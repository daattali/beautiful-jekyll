import datetime
import json
import urllib.request

import pandas as pd
import tabula

QUERY_HEADERS = {
    'User-Agent': 'Mozilla/5.0',
}
FIREBASE_BATCH_SIZE = 499  # Max = 500


def batch_data(iterable, n=1):
    """Divide data into batches of fix length."""
    l = len(iterable)
    for ndx in range(0, l, n):
        yield iterable[ndx:min(ndx + n, l)]


class Dataset(object):
    def __init__(self, url, name):
        self.url = url
        self.name = name
        self.dataframe = None

    def query_all(self, **kwargs):
        if self.dataframe is None:
            self.dataframe = self._create_dataframe()
            self._localize(**kwargs)
            self._cleanse(**kwargs)

        return self.dataframe

    def _create_dataframe(self):
        raise NotImplementedError()

    def _localize_date(self, column, na_value='Đang điều tra'):
        t = self.dataframe[column].str.extract(r'([0-9]+)月([0-9]+)日')
        self.dataframe[column] = (t[0] + '/' + t[1]).fillna(na_value)
        return self.dataframe[column]

    def _localize_age(self, column, na_value='Đang điều tra'):
        self.dataframe[column] = self.dataframe[column].str.replace('代', 's')
        self.dataframe[column].replace({
            '未就学児': 'Dưới 3',
            '就学児': '3-9',
            '10歳未': 'Dưới 10',
            '100歳以': 'Trên 100',
            '不': 'Không rõ',
            '調査中': 'Đang điều tra',
        }, inplace=True)
        self.dataframe[column].fillna(na_value, inplace=True)
        return self.dataframe[column]

    def _localize_sex(self, column, na_value='Đang điều tra'):
        self.dataframe[column].replace({
            '男性': 'Nam',
            '女性': 'Nữ',
            '女児': 'Nữ',
            '調査中': 'Đang điều tra',
        }, inplace=True)
        self.dataframe[column].fillna(na_value, inplace=True)
        return self.dataframe[column]

    def _localize(self, **kwargs):
        pass

    def _cleanse(self, **kwargs):
        pass

    def save_csv(self, save_path=None, index=False):
        if save_path is None:
            now = datetime.datetime.now()
            timestamp = now.strftime('%Y%m%d_%H%M')
            save_path = f'{timestamp}_{self.name}.csv'

        self.dataframe.to_csv(save_path, index=index)

    def to_dict(self, orient='record', replace_nan=False):
        data = self.dataframe.where(self.dataframe.notnull(), None) if replace_nan else self.dataframe
        return data.to_dict(orient=orient)

    def to_json(self):
        dict_data = self.to_dict(replace_nan=True)
        json_data = json.dumps(dict_data)
        return json_data

    def upload_to_storage(self, bucket, extension='json'):
        """Upload a Dataframe as JSON to Firebase Storage.

        returns
            storage_ref
        """
        storage_ref = f'{self.name}.{extension}'
        blob = bucket.blob(storage_ref)

        if extension == 'json':
            data_str = self.to_json()
        else:
            raise NotImplementedError(f'Unsupported file type "{extension}"')

        blob.upload_from_string(data_str, content_type='application/json')

        return storage_ref

    def upload_to_database(self, client, root, item_key=None, batch_size=FIREBASE_BATCH_SIZE):
        if item_key not in self.dataframe.columns:
            item_key = None
        data_dict = self.to_dict()
        for batched_data in batch_data(data_dict, batch_size):
            batch = client.batch()
            for data_item in batched_data:
                if item_key is not None:
                    doc_ref = client.collection(root).document(str(data_item[item_key]))
                else:
                    doc_ref = client.collection(root).document()
                batch.set(doc_ref, data_item)
            batch.commit()


class CsvDataset(Dataset):
    def __init__(self, url, name):
        super().__init__(url, name)

    def _create_dataframe(self):
        return pd.read_csv(self.url)


class ExcelDataset(Dataset):
    def __init__(self, url, name, sheet_id, header_row=0):
        super().__init__(url, name)
        self.sheet = sheet_id
        self.header_row = header_row

    def _create_dataframe(self):
        return pd.read_excel(self.url, self.sheet, header=self.header_row)


class JsonDataset(Dataset):
    def __init__(self, url, name, data_key=None):
        super().__init__(url, name)
        self.json = None

    def _get_json_from_url(self):
        request = urllib.request.Request(self.url, headers=QUERY_HEADERS)
        with urllib.request.urlopen(request) as url:
            data = json.loads(url.read().decode())
        return data

    def _create_dataframe(self):
        if self.json is None:
            self.json = self._get_json_from_url()
        return self._create_dataframe_from_json()

    def _create_dataframe_from_json(self):
        raise NotImplementedError()


class PdfDataset(Dataset):
    def __init__(self, url, name, pages='all', include_header=True, **kwargs):
        super().__init__(url, name)
        self.pages = pages
        self.include_header = include_header
        self.kwargs = kwargs

    def _create_dataframe(self):
        if self.include_header:
            df = tabula.read_pdf(self.url, pages=self.pages, **self.kwargs)
        else:
            df = tabula.read_pdf(self.url, pages=self.pages, pandas_options={'header': None}, **self.kwargs)

        if isinstance(df, list):
            df = pd.concat(df)
        return df.reset_index()
