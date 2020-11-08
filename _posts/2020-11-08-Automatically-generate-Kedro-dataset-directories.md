---
layout: post
title: Automatically creating Kedro dataset directories 
subtitle: Avoiding IO errors at the end of pipelines with a simple hook.
tags: [code]
comments: true
---

If you use Kedro for data pipelines, you may have had issues saving datasets if the dataset directory does not already exist. Instead of manually creating these data folders, here is a hook which automatically creates any missing directories. In the process, it'll also automatically generate a `.gitkeep` file.

```python
import logging
import os
from pathlib import Path

from kedro.framework.hooks import hook_impl

logger = logging.getLogger(__name__)


class CreateDatasetFoldersHook:
    """
    For each dataset in the Kedro catalog, recursively create parent directories.

    This prevents the sad situation where at the end of a pipeline run, the job fails with an IO error.

    See https://discourse.kedro.community/t/how-do-i-access-each-dataset-s-dataset-fpath-attribute/164
    """

    @staticmethod
    @hook_impl
    def after_catalog_created(catalog, conf_catalog, conf_creds, feed_dict, save_version, load_versions, run_id):
        entries = catalog.list()
        for entry in entries:
            try:
                dset = getattr(catalog.datasets, entry)

                if hasattr(dset, "_path"):
                    _make_dirs(dset._path)
                elif hasattr(dset, "_filepath"):
                    _make_dirs(dset._filepath)
                # some dataset types do not have either of these attributes.
                else:
                    pass
            # catalog.list() includes params. These will cause trouble if you try to load
            # from the catalog.datasets
            except AttributeError:
                pass


def _make_dirs(path_to_make):
    if not os.path.exists(path_to_make):
        logger.info(f"Creating missing path {path_to_make}")
        os.makedirs(path_to_make)
    # creates a .gitkeep file while we're at it
    Path(os.path.join(path_to_make, ".gitkeep")).touch()
```




Credit to [DataEngineerOne](https://www.youtube.com/c/DataEngineerOne), who guided me in the right direction on the [kedro.community forum](https://discourse.kedro.community/t/how-do-i-access-each-dataset-s-dataset-fpath-attribute/164/2?u=facepalm).

