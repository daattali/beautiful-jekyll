---
layout: post
title: How to do stratified splitting of Multi-class Multi-labeled image classification data
subtitle: Complete with code and unit tests.
tags: [code]
comments: true
---

I saw a [post on StackOverflow](https://stackoverflow.com/questions/64838108/multi-labeled-image-classification-with-imbalanced-data-how-to-split-it) about how to do stratified sampling with multi-class, multi-label image data. I had some code which solves this exact problem, so I am making this available here as-is.

The solution depends on `skmultilearn`'s `IterativeStratification` method. Unfortunately, `skmultilearn` is not very well maintained and I ran into a few sharp corners while coming up with this solution. I documented those sharp corners in the comments below.

Also note that these function is used inside a Kedro pipeline, where I am using Kedro's PartitionDatasets. That's why the return values are sometimes packaged inside a dictionary.

I am also making available my `pytest` suites at the end.


```python
import pandas as pd
import numpy as np
from typing import Any, Callable, Dict, List, Optional, Set, Tuple, Union

import ipytest
import pytest
from typeguard import typechecked
from skmultilearn.model_selection.iterative_stratification import IterativeStratification

# enables ipytest notebook magic
ipytest.autoconfig()

logger = logging.getLogger(__name__)
```


```python
@typechecked
def stratify_shuffle_split_subsets(
    full_dataset: Dict[str, Callable], output_partition_name: str, train_fraction: float
) -> Tuple[pd.DataFrame, Dict[str, pd.DataFrame], Dict[str, pd.DataFrame]]:
    """
    Stratify-shuffle-split the a multi-class multi-label dataset into
    train/dev/validation sets.

    Args:
        full_dataset: the full supervised dataset. One column is the img uris, and the rest are binary labels.
        output_partition_name: the name of the output partition
        train_fraction: the fraction of data to reserve for the training dataset. The remaining data will be evenly
            split into the dev and validation subsets.

    Returns:
        the supervised dataset, split into train/test/dev subsets. The train subset is not saved as a partitionedDataset
        yet because we are doing label smoothing in the next processing step.
    """
    if not 0 < train_fraction < 1:
        raise ValueError(f"Training fraction must be value between 0 and 1, got {train_fraction}")

    loader = full_dataset[output_partition_name]
    full_dataset = loader()
    original_cols = full_dataset.columns
    # pandas documentation says to use .to_numpy() instead of .values for consistency
    img_urls = full_dataset["img_url"].to_numpy()

    # sanity check: no duplicate labels
    if not len(img_urls) == len(set(img_urls)):
        raise ValueError("Duplicate image keys detected.")

    labels = full_dataset.drop(columns=["img_url"]).to_numpy().astype(int)
    # NOTE generators are replicated across workers. do stratified shuffle split beforehand
    logger.info("stratifying dataset iteratively. this may take a while.")
    # NOTE: splits >2 broken; https://github.com/scikit-multilearn/scikit-multilearn/issues/209
    # so, do 2 rounds of iterative splitting
    stratifier = IterativeStratification(
        n_splits=2, order=2, sample_distribution_per_fold=[1.0 - train_fraction, train_fraction],
    )
    # this class is a generator that produces k-folds. we just want to iterate it once to make a single static split
    # NOTE: needs to be computed on hard labels.
    train_indexes, everything_else_indexes = next(stratifier.split(X=img_urls, y=labels))

    num_overlapping_samples = len(set(train_indexes).intersection(set(everything_else_indexes)))
    if num_overlapping_samples != 0:
        raise ValueError(f"First splitting failed, {num_overlapping_samples} overlapping samples detected")

    # s3url array shape (N_samp,)
    x_train, x_else = img_urls[train_indexes], img_urls[everything_else_indexes]
    # labels array shape (N_samp, n_classes)
    Y_train, Y_else = labels[train_indexes, :], labels[everything_else_indexes, :]

    # now, split the "else" data evenly into dev/val splits
    stratifier = IterativeStratification(n_splits=2, order=2)  # splits evenly by default
    dev_indexes, validation_indexes = next(stratifier.split(x_else, Y_else))

    num_overlapping_samples = len(set(dev_indexes).intersection(set(validation_indexes)))
    if num_overlapping_samples != 0:
        raise ValueError(f"Second splitting failed, {num_overlapping_samples} overlapping samples detected")

    x_dev, x_val = (x_else[dev_indexes], x_else[validation_indexes])
    Y_dev, Y_val = (Y_else[dev_indexes, :], Y_else[validation_indexes, :])

    for subset_name, frac, encodings_collection in [
        ("train", train_fraction, Y_train),
        ("dev", (1.0 - train_fraction) / 2, Y_dev),
        ("val", (1.0 - train_fraction) / 2, Y_val),
    ]:
        # column-wise sum. sum(counts) > n_samples due to imgs with >1 class
        count_values = np.sum(encodings_collection, axis=0)
        # skip first col, which is the image key, not a class ID
        counts = {class_id: count_val for class_id, count_val in zip(full_dataset.columns[1:], count_values)}
        logger.info(f" {subset_name} subset ({frac * 100:.1f}%) encodings counts after stratification: {counts}")

    # combine (x,y) data into dataframes
    train_subset = pd.DataFrame(Y_train)
    train_subset.insert(0, "img_url", pd.Series(x_train))
    train_subset.columns = original_cols

    dev_subset = pd.DataFrame(Y_dev)
    dev_subset.insert(0, "img_url", pd.Series(x_dev))
    dev_subset.columns = original_cols

    val_subset = pd.DataFrame(Y_val)
    val_subset.insert(0, "img_url", pd.Series(x_val))
    val_subset.columns = original_cols

    # TODO create Great Expectations suite for this node instead
    assert "img_url" in dev_subset.columns
    assert "img_url" in val_subset.columns
    assert "img_url" in train_subset.columns

    return (
        train_subset,
        {output_partition_name: dev_subset},
        {output_partition_name: val_subset},
    )
```

# Testing that it all works

Below are my pytests and their results. Note, that the fixtures mimic Kedro PartitionDatasets.


```python
@pytest.fixture
def unsplit_supervised_learning_dataset_partition_name():
    """PartitionName to simulate Kedro PartitionDataset"""
    return "pytest_unsplit_supervised_learning_dataset_partition_name"


@pytest.fixture
def unsplit_supervised_learning_dataset(unsplit_supervised_learning_dataset_partition_name: str) -> Dict[str, Callable]:
    """
    Generates a multi-class multilabel dataset.

    Args:
        unsplit_supervised_learning_dataset_partition_name:

    Returns:
        a multi-class multi-label df, packed in a lambda to mimic Kedro PartitionDataset
    """
    df_rows = []

    n_total = 60
    n_created = 0
    n_class1 = n_total // 3
    n_class2 = n_total // 3
    n_class2_plus_3 = n_total // 3

    for _ in range(n_class1):
        df_rows.append({"img_url": f"s3://test{n_created}", "class0": 1, "class1": 0, "class2": 0})
        n_created += 1

    for _ in range(n_class2):
        df_rows.append({"img_url": f"s3://test{n_created}", "class0": 0, "class1": 1, "class2": 0})
        n_created += 1

    for _ in range(n_class2_plus_3):
        df_rows.append({"img_url": f"s3://test{n_created}", "class0": 0, "class1": 1, "class2": 1})
        n_created += 1

    df = pd.DataFrame(df_rows)
    data_loader = lambda: df

    return {unsplit_supervised_learning_dataset_partition_name: data_loader}


@pytest.mark.parametrize("train_fraction", [-1.0, 0, 1, 5])
def test_train_fraction_range(
    unsplit_supervised_learning_dataset, train_fraction, unsplit_supervised_learning_dataset_partition_name
):
    """
    Tests that train_fraction is validated between 0, 1.
    """
    with pytest.raises(ValueError):
        stratify_shuffle_split_subsets(
            full_dataset=unsplit_supervised_learning_dataset,
            output_partition_name=unsplit_supervised_learning_dataset_partition_name,
            train_fraction=train_fraction,
        )


def test_duplicate_uris_detected(unsplit_supervised_learning_dataset_partition_name):
    """Tests whether duplicate image keys are properly detected"""
    # setup

    df = pd.DataFrame(
        [
            {"img_url": "s3://duplicate1", "class0": 1, "class1": 0, "class2": 0},
            {"img_url": "s3://duplicate1", "class0": 1, "class1": 0, "class2": 0},
            {"img_url": "s3://duplicate1", "class0": 1, "class1": 0, "class2": 0},
            {"img_url": "s3://duplicate2", "class0": 0, "class1": 1, "class2": 0},
            {"img_url": "s3://duplicate2", "class0": 0, "class1": 1, "class2": 0},
        ]
    )
    data_loader = lambda: df
    partition_dset = {unsplit_supervised_learning_dataset_partition_name: data_loader}

    # test
    with pytest.raises(ValueError):
        stratify_shuffle_split_subsets(
            full_dataset=partition_dset,
            output_partition_name=unsplit_supervised_learning_dataset_partition_name,
            train_fraction=0.6,
        )

        
def test_col_names_same(unsplit_supervised_learning_dataset, unsplit_supervised_learning_dataset_partition_name):
    """
    Tests that train_fraction is validated between 0, 1.
    """
    # setup
    train_split: pd.DataFrame
    dev_split: Dict[str, pd.DataFrame]
    val_split: Dict[str, pd.DataFrame]
    # set train fraction to 0.6 to make math easier later
    train_fraction = 0.6
    data_loader = unsplit_supervised_learning_dataset[unsplit_supervised_learning_dataset_partition_name]
    original_df = data_loader()
    original_df_cols = original_df.columns

    # run
    train_df, dev_split, val_split = stratify_shuffle_split_subsets(
        full_dataset=unsplit_supervised_learning_dataset,
        output_partition_name=unsplit_supervised_learning_dataset_partition_name,
        train_fraction=train_fraction,
    )

    # test setup
    dev_df, val_df = (
        dev_split[unsplit_supervised_learning_dataset_partition_name],
        val_split[unsplit_supervised_learning_dataset_partition_name],
    )
    train_df_cols, dev_df_cols, val_df_cols = train_df.columns, dev_df.columns, val_df.columns

    # tests
    assert all(train_df_cols == original_df_cols)
    assert all(dev_df_cols == original_df_cols)
    assert all(val_df_cols == original_df_cols)

    
def test_stratify_shuffle_split_subsets(
    unsplit_supervised_learning_dataset, unsplit_supervised_learning_dataset_partition_name
):
    """Tests whether a multi-class multi-label dataset gets properly stratify-shuffle-split."""
    # setup
    train_split: pd.DataFrame
    dev_split: Dict[str, pd.DataFrame]
    val_split: Dict[str, pd.DataFrame]
    # set train fraction to 0.6 to make math easier later
    train_fraction = 0.6
    ratio_train_to_val = train_fraction / ((1.0 - train_fraction) / 2)
    data_loader = unsplit_supervised_learning_dataset[unsplit_supervised_learning_dataset_partition_name]
    original_dset_len = len(data_loader())

    # run
    train_df, dev_split, val_split = stratify_shuffle_split_subsets(
        full_dataset=unsplit_supervised_learning_dataset,
        output_partition_name=unsplit_supervised_learning_dataset_partition_name,
        train_fraction=train_fraction,
    )

    # test setup
    dev_df, val_df = (
        dev_split[unsplit_supervised_learning_dataset_partition_name],
        val_split[unsplit_supervised_learning_dataset_partition_name],
    )
    train_keys, dev_keys, val_keys = train_df["img_url"], dev_df["img_url"], val_df["img_url"]

    uniq_train_keys, uniq_dev_keys, uniq_val_keys = set(train_keys), set(dev_keys), set(val_keys)

    # Tests

    ## test keys

    # test no duplicate keys within subsets
    assert len(train_keys) == len(uniq_train_keys)
    assert len(val_keys) == len(uniq_val_keys)
    assert len(dev_keys) == len(uniq_dev_keys)

    # test that all subsets have mutually exclusive S3 URIs
    assert len(uniq_train_keys.intersection(uniq_dev_keys)) == 0
    assert len(uniq_train_keys.intersection(uniq_val_keys)) == 0
    assert len(uniq_val_keys.intersection(uniq_dev_keys)) == 0

    ## test ratios
    # test that dev and val subsets get same number of samples
    assert len(dev_df) == len(val_df)
    # test that test set is 2x size of dev
    assert len(train_df) / (len(train_df) + len(dev_df) + len(val_df)) == pytest.approx(train_fraction)
    # test that all samples are used
    assert len(train_df) + len(dev_df) + len(val_df) == original_dset_len

    ## test distributions

    ### class 0
    # test whether dev/val set got same amount of class 0
    assert len(dev_df[dev_df.class0 == 1]) == len(val_df[val_df.class0 == 1])
    # test whether train set got 2x class0 as val set
    assert len(train_df[train_df.class0 == 1]) / len(val_df[val_df.class0 == 1]) == pytest.approx(ratio_train_to_val)

    ### class 1
    # test whether dev/val set got same amount of class 1
    assert len(dev_df[dev_df.class1 == 1]) == len(val_df[val_df.class1 == 1])
    # test whether train set got 2x class1 as val set
    assert len(train_df[train_df.class1 == 1]) / len(val_df[val_df.class1 == 1]) == pytest.approx(ratio_train_to_val)

    ### class 2
    # test whether dev/val set got same amount of class 2
    assert len(dev_df[dev_df.class2 == 1]) == len(val_df[val_df.class2 == 1])
    # test whether train set got 2x class1 as val set
    assert len(train_df[train_df.class2 == 1]) / len(val_df[val_df.class2 == 1]) == pytest.approx(ratio_train_to_val)

```


```python
ipytest.run()
```

    .....2020-11-22 17:19:46,228 - __main__ - INFO - stratifying dataset iteratively. this may take a while.
    2020-11-22 17:19:46,239 - __main__ - INFO -  train subset (60.0%) encodings counts after stratification: {'class0': 12, 'class1': 24, 'class2': 12}
    2020-11-22 17:19:46,251 - __main__ - INFO -  dev subset (20.0%) encodings counts after stratification: {'class0': 4, 'class1': 8, 'class2': 4}
    2020-11-22 17:19:46,253 - __main__ - INFO -  val subset (20.0%) encodings counts after stratification: {'class0': 4, 'class1': 8, 'class2': 4}
    .2020-11-22 17:19:46,271 - __main__ - INFO - stratifying dataset iteratively. this may take a while.
    2020-11-22 17:19:46,280 - __main__ - INFO -  train subset (60.0%) encodings counts after stratification: {'class0': 12, 'class1': 24, 'class2': 12}
    2020-11-22 17:19:46,283 - __main__ - INFO -  dev subset (20.0%) encodings counts after stratification: {'class0': 4, 'class1': 8, 'class2': 4}
    2020-11-22 17:19:46,287 - __main__ - INFO -  val subset (20.0%) encodings counts after stratification: {'class0': 4, 'class1': 8, 'class2': 4}
    .                                                                                         [100%]
    ========================================== warnings summary ===========================================
    /home/richard/src/DENDRA/seeweed/venv/lib/python3.7/site-packages/_pytest/config/__init__.py:1040
      /home/richard/src/DENDRA/seeweed/venv/lib/python3.7/site-packages/_pytest/config/__init__.py:1040: PytestAssertRewriteWarning: Module already imported so cannot be rewritten: typeguard
        self._mark_plugins_for_rewrite(hook)
    
    -- Docs: https://docs.pytest.org/en/stable/warnings.html
    7 passed, 1 warning in 0.15s



If you found this useful, feel free to upvote the linked StackOverflow question.
