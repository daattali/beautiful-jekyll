import json
import re
import urllib.request
import sys
import traceback

import firebase_admin
from firebase_admin import credentials, firestore, storage
import pandas as pd
import tabula

import datasets
import localization


FIREBASE_APP_NAME = 'thongtincovid19-4dd12'
FIREBASE_PRIVATE_KEY = './thongtincovid19_serviceaccount_privatekey.json'
FIREBASE_STORAGE_BUCKET = 'gs://thongtincovid19-4dd12.appspot.com'


class TokyoPatientsDataset(datasets.CsvDataset):
    URL = 'https://stopcovid19.metro.tokyo.lg.jp/data/130001_tokyo_covid19_patients.csv'
    NAME = 'patient-tokyo'

    COL_NO = 'STT'
    COL_AREA_CODE = 'Mã vùng'
    COL_PREFECTURE = 'Tỉnh/Thành phố'
    COL_DISTRICT = 'Quận/Huyện'
    COL_PUBLISHED_DATE = 'Ngày công bố'
    COL_DOW = 'Thứ'
    COL_SYMPTOM_DATE = 'Ngày phát hiện triệu chứng'
    COL_PATIENT_ADDRESS = 'Nơi sinh sống'
    COL_PATIENT_AGE = 'Độ tuổi'
    COL_PATIENT_SEX = 'Giới tính'
    COL_PATIENT_ATTRIBUTE = 'Đặc tính'
    COL_PATIENT_STATE = 'Tình trạng'
    COL_PATIENT_SYMPTOM = 'Triệu chứng'
    COL_PATIENT_TRAVEL = 'Có lịch sử đi lại hay không'
    COL_REF = 'Tham khảo'
    COL_DISCHARGED = 'Đã ra viện hay chưa'

    def __init__(self, **kwargs):
        super().__init__(self.URL, self.NAME, **kwargs)

    def _localize(self):
        # Localize column name
        self.dataframe.columns = [
            self.COL_NO,
            self.COL_AREA_CODE,
            self.COL_PREFECTURE,
            self.COL_DISTRICT,
            self.COL_PUBLISHED_DATE,
            self.COL_DOW,
            self.COL_SYMPTOM_DATE,
            self.COL_PATIENT_ADDRESS,
            self.COL_PATIENT_AGE,
            self.COL_PATIENT_SEX,
            self.COL_PATIENT_ATTRIBUTE,
            self.COL_PATIENT_STATE,
            self.COL_PATIENT_SYMPTOM,
            self.COL_PATIENT_TRAVEL,
            self.COL_REF,
            self.COL_DISCHARGED,
        ]

        # Localize data
        self.dataframe[self.COL_PREFECTURE].replace({
            '東京都': 'Tokyo'
        }, inplace=True)
        self.dataframe[self.COL_DOW].replace({
            '日': 'CN',
            '月': '2',
            '火': '3',
            '水': '4',
            '木': '5',
            '金': '6',
            '土': '7',
        }, inplace=True)
        self.dataframe[self.COL_PATIENT_ADDRESS].replace({
            '湖北省武漢市': 'Vũ Hán, Hồ Bắc',
            '湖南省長沙市': 'Trường Sa, Hồ Nam',
            '都内': 'Nội đô Tokyo',
            '都外': 'Ngoài Tokyo',
            '調査中': 'Đang điều tra',
            **localization.PREFECTURES,
        }, inplace=True)
        self.dataframe[self.COL_PATIENT_SEX].replace({
            '男性': 'Nam',
            '女性': 'Nữ',
            '不明': 'Không rõ',
            '調査中': 'Đang điều tra',
        }, inplace=True)
        self.dataframe[self.COL_PATIENT_AGE] = self.dataframe[self.COL_PATIENT_AGE].str.replace('代', 's')
        self.dataframe[self.COL_PATIENT_AGE].replace({
            '10歳未': 'Dưới 10',
            '100歳以': 'Trên 100',
            '不': 'Không rõ',
        }, inplace=True)

        return self.dataframe

    def _cleanse(self, auto_drop=False):
        # Fill missing data
        self.dataframe[self.COL_PATIENT_ADDRESS].fillna('―', inplace=True)

        if auto_drop:
            # Drop meaningless columns (less than 1 unique value)
            self.dataframe.drop(columns=[
                self.COL_AREA_CODE,
                self.COL_PREFECTURE,
                self.COL_DISTRICT,
                self.COL_SYMPTOM_DATE,
                self.COL_PATIENT_ATTRIBUTE,
                self.COL_PATIENT_STATE,
                self.COL_PATIENT_SYMPTOM,
                self.COL_PATIENT_TRAVEL,
                self.COL_REF,
                self.COL_DISCHARGED,
            ], inplace=True)

        return self.dataframe


class PrefectureByDateDataset(datasets.JsonDataset):
    URL = 'https://www3.nhk.or.jp/news/special/coronavirus/data/47newpatients-data.json'
    NAME = 'prefecture-by-date'

    COL_PREFECTURE = 'Tỉnh/Thành phố'
    COL_TOTAL = 'Tổng'

    def __init__(self, **kwargs):
        super().__init__(self.URL, self.NAME, **kwargs)

    def _create_dataframe_from_json(self):
        formatted_list = []
        for pref in self.json['data47']:
            formatted_list.append([pref['name']] + pref['data'] + [sum(pref['data'])])
        dates = self.json['category']
        self.dataframe = pd.DataFrame(
            formatted_list,
            columns=[self.COL_PREFECTURE] + dates + [self.COL_TOTAL]
        )

        return self.dataframe

    def _localize(self):
        self.dataframe[self.COL_PREFECTURE].replace(localization.PREFECTURES, inplace=True)
        return self.dataframe


class PatientDetailsDataset(datasets.JsonDataset):
    URL = (
        'https://services8.arcgis.com/JdxivnCyd1rvJTrY/ArcGIS/rest/services/v2_covid19_list_csv/FeatureServer/0/'
        'query?where=1=1'
        '&geometryType=esriGeometryEnvelope'
        '&spatialRel=esriSpatialRelIntersects'
        '&resultType=none'
        '&distance=0.0'
        '&units=esriSRUnit_Meter'
        '&returnGeodetic=false'
        '&outFields=*'
        '&returnGeometry=false'
        '&featureEncoding=esriDefault'
        '&multipatchOption=xyFootprint&'
        '&applyVCSProjection=false'
        '&returnIdsOnly=false'
        '&returnUniqueIdsOnly=false'
        '&returnCountOnly=false'
        '&returnExtentOnly=false'
        '&returnQueryGeometry=false'
        '&returnDistinctValues=false'
        '&cacheHint=false'
        '&resultRecordCount=0'
        '&returnZ=false'
        '&returnM=false'
        '&returnExceededLimitFeatures=true'
        '&sqlFormat=none'
        '&f=pjson'
    )
    NAME = 'patient-all'

    COL_DATE = 'Date'

    def __init__(self, **kwargs):
        super().__init__(self.URL, self.NAME, **kwargs)

    def _create_dataframe_from_json(self):
        self.dataframe = pd.DataFrame([entry['attributes'] for entry in self.json['features']])
        return self.dataframe

    def _cleanse(self):
        self.dataframe[self.COL_DATE].fillna(0, inplace=True)
        self.dataframe[self.COL_DATE] = pd.to_datetime(self.dataframe[self.COL_DATE], unit='ms')
        self.dataframe[self.COL_DATE] = self.dataframe[self.COL_DATE].dt.strftime('%Y%m%d %H:%M')
        return self.dataframe[self.COL_DATE]


class PatientByCityTokyoDataset(datasets.JsonDataset):
    URL = 'https://raw.githubusercontent.com/tokyo-metropolitan-gov/covid19/development/data/patient.json'
    NAME = 'patient-by-city-tokyo'

    COL_CODE = 'code'
    COL_AREA = 'area'
    COL_LABEL = 'label'
    COL_RUBY = 'ruby'
    COL_COUNT = 'count'
    COL_AREA_VIETNAMESE = 'area_vietnamese'
    COL_LABEL_VIETNAMESE = 'label_vietnamese'

    def __init__(self, **kwargs):
        super().__init__(self.URL, self.NAME, **kwargs)

    def _create_dataframe_from_json(self):
        return pd.DataFrame(self.json['datasets']['data'])

    def _cleanse(self):
        self.dataframe[self.COL_CODE].fillna(0, inplace=True)
        self.dataframe[self.COL_CODE] = self.dataframe[self.COL_CODE].astype(int)

        self.dataframe[self.COL_AREA].fillna('-', inplace=True)
        self.dataframe[self.COL_RUBY].fillna('-', inplace=True)

        return self.dataframe

    def _localize(self):
        self.dataframe[self.COL_LABEL_VIETNAMESE] = self.dataframe[self.COL_LABEL].replace({
            **localization.TOKYO_CITIES,
            '都外': 'Ngoài Tokyo',
            '調査中': 'Đang điều tra',
            '小計': 'Tổng số',
        })
        self.dataframe[self.COL_AREA_VIETNAMESE] = self.dataframe[self.COL_AREA].replace({
            '特別区': '23 quận lớn',
            '多摩地域': 'Địa phận Tama',
            '島しょ地域': 'Các đảo nhỏ',
        })
        return self.dataframe


class PatientByCityOsakaDataset(datasets.ExcelDataset):
    URL = 'https://github.com/codeforosaka/covid19/blob/development/data/patients_and_inspections.xlsx?raw=true'
    NAME = 'patient-by-city-osaka'
    SHEET = 1
    HEADER = 1

    COL_ID = 'Id'
    COL_PUBLISHED_DATE = 'Published date'
    COL_AGE = 'Age'
    COL_SEX = 'Sex'
    COL_LOCATION = 'Location'
    COL_SYMPTOM_DATE = 'Symptom date'
    COL_STATUS = 'Status'
    COL_DISCHARGED = 'Discharged'

    def __init__(self, **kwargs):
        super().__init__(self.URL, self.NAME, self.SHEET, self.HEADER, **kwargs)

    def _cleanse(self):
        self.dataframe[self.COL_PUBLISHED_DATE] = self.dataframe[self.COL_PUBLISHED_DATE].astype(str)
        self.dataframe[self.COL_SYMPTOM_DATE] = self.dataframe[self.COL_SYMPTOM_DATE].astype(str)
        return self.dataframe

    def _localize(self):
        self.dataframe.columns = [
            self.COL_ID,
            self.COL_PUBLISHED_DATE,
            self.COL_AGE,
            self.COL_SEX,
            self.COL_LOCATION,
            self.COL_SYMPTOM_DATE,
            self.COL_STATUS,
            self.COL_DISCHARGED,
        ]
        self.dataframe[self.COL_AGE].replace({
            '未就学児': 'Dưới 3',
            '就学児': '3-9',
        }, inplace=True)
        self.dataframe[self.COL_SEX].replace({
            '女性': 'Female',
            '男性': 'Male',
        }, inplace=True)
        self.dataframe[self.COL_LOCATION].replace({
            **localization.OSAKA_CITIES,
            '府外': 'Ngoài Osaka',
            '大阪府外': 'Ngoài Osaka',
            '調査中': 'Đang điều tra',
        }, inplace=True)
        self.dataframe[self.COL_DISCHARGED].replace({
            '退院': 'Ra viện',
            '死亡退院': 'Tử vong',
            '入院中': 'Đang nằm viện',
            '入院調整中': 'Chuẩn bị nhập viện',
            '管外': 'Không quản lý',
        }, inplace=True)

        return self.dataframe


class PatientByCitySaitamaDataset(datasets.PdfDataset):
    BASE_URL = 'https://www.pref.saitama.lg.jp/'
    URL = 'https://www.pref.saitama.lg.jp/a0701/covid19/jokyo.html'
    NAME = 'patient-by-city-saitama'

    COL_ID = 'Id'
    COL_REF = 'Ref'
    COL_DATE = 'Date'
    COL_AGE = 'Age'
    COL_SEX = 'Sex'
    COL_LOCATION = 'Location'

    def __init__(self, **kwargs):
        super().__init__(self._find_url(), self.NAME, include_header=False, **kwargs)

    def _find_url(self):
        request = urllib.request.Request(self.URL, headers=datasets.QUERY_HEADERS)
        with urllib.request.urlopen(request) as url:
            dom = url.read().decode()

        pattern = r'<a [^>]*href="([^"]+)">陽性確認者一覧[^<]*</a>'
        url = re.search(pattern, dom).group(1)
        return f'{self.BASE_URL}{url}'

    def _localize(self):
        self.dataframe = self.dataframe.iloc[:, 1:]
        self.dataframe.columns = [
            self.COL_ID,
            self.COL_REF,
            self.COL_DATE,
            self.COL_AGE,
            self.COL_SEX,
            self.COL_LOCATION,
        ]
        self.dataframe.drop(index=0, inplace=True)
        self._localize_date(self.COL_DATE)
        self._localize_age(self.COL_AGE)
        self._localize_sex(self.COL_SEX)

        self.dataframe[self.COL_LOCATION].replace({
            **localization.SAITAMA_CITIES,
            '調査中': 'Đang điều tra',
            '川口市外': 'Ngoài Kawaguchi',
            '県外': 'Ngoài tỉnh',
            '埼玉県外': 'Ngoài tỉnh',
            '埼玉県': 'Tỉnh Saitama',
            '東京都': 'Tokyo',
        }, inplace=True)
        self.dataframe[self.COL_LOCATION].fillna('Đang điều tra', inplace=True)

        return self.dataframe


class PatientByCityKanagawaDataset(datasets.CsvDataset):
    URL = 'http://www.pref.kanagawa.jp/osirase/1369/data/csv/patient.csv'
    NAME = 'patient-by-city-kanagawa'

    COL_DATE = 'Date'
    COL_LOCATION = 'Location'
    COL_AGE = 'Age'
    COL_SEX = 'Sex'

    def __init__(self, **kwargs):
        super().__init__(self.URL, self.NAME, **kwargs)

    def _localize(self):
        self.dataframe.columns = [
            self.COL_DATE,
            self.COL_LOCATION,
            self.COL_AGE,
            self.COL_SEX,
        ]

        self.dataframe[self.COL_LOCATION] = self.dataframe[self.COL_LOCATION].str.replace('神奈川県', '')
        self.dataframe[self.COL_LOCATION] = self.dataframe[self.COL_LOCATION].str.replace('内', '')
        self.dataframe[self.COL_LOCATION] = self.dataframe[self.COL_LOCATION].str.replace('保健所管', '')
        self.dataframe[self.COL_LOCATION] = self.dataframe[self.COL_LOCATION].str.replace('及び都', '')
        self.dataframe[self.COL_LOCATION] = self.dataframe[self.COL_LOCATION].str.replace('保健福祉事務所管', '市')
        self.dataframe[self.COL_LOCATION].replace({
            **localization.KANAGAWA_CITIES,
            '': 'Tỉnh Kanagawa',
            'スペイン（横浜市発表）': 'Yokohama',
            '国外（川崎市発表）': 'Kawasaki',
            '川崎市外（川崎市発表）': 'Kawasaki',
            '茅ケ崎市保健所管内及び都内': 'Chigasaki',
            '川崎市外': 'Ngoài Kawasaki',
            '横浜市外': 'Ngoài Yokohama',
            '東京都\u3000': 'Tokyo',
        }, inplace=True)

        self._localize_age(self.COL_AGE)
        self._localize_sex(self.COL_SEX)

        return self.dataframe


class ClinicDataset(datasets.CsvDataset):
    COL_ID = 'Id'
    COL_NAME = 'Name'
    COL_POSTAL_CODE = 'Postal Code'
    COL_ADDRESS = 'Address'
    COL_TEL = 'Tel'
    COL_WEBSITE = 'Website'

    def __init__(self, url, name, **kwargs):
        super().__init__(url, name, **kwargs)

    def _localize(self):
        pass

    def _cleanse(self):
        self.dataframe = self.dataframe.iloc[:, :6]

        self.dataframe.columns = [
            self.COL_ID,
            self.COL_NAME,
            self.COL_POSTAL_CODE,
            self.COL_ADDRESS,
            self.COL_TEL,
            self.COL_WEBSITE,
        ]

        self.dataframe = self.dataframe[self.dataframe[self.COL_ID].notnull()]
        self.dataframe = self.dataframe[self.dataframe[self.COL_POSTAL_CODE].notnull()]
        self.dataframe[self.COL_ID] = self.dataframe[self.COL_ID].astype(int)
        self.dataframe[self.COL_POSTAL_CODE] = self.dataframe[self.COL_POSTAL_CODE].astype(str)
        self.dataframe.fillna('なし', inplace=True)

        for column in [
            self.COL_NAME,
            self.COL_POSTAL_CODE,
            self.COL_ADDRESS,
            self.COL_TEL,
            self.COL_WEBSITE,
        ]:
            self.dataframe[column] = self.dataframe[column].str.replace('\r', '')

        return self.dataframe


def init_firebase_app():
    cred = credentials.Certificate(FIREBASE_PRIVATE_KEY)
    app = firebase_admin.initialize_app(cred, {
        'storageBucket': f'{FIREBASE_APP_NAME}.appspot.com'
    })
    client = firestore.client()
    bucket = storage.bucket(app=app)

    return app, client, bucket


def get_data_from_mhlw():
    CRAWL_URL = 'https://www.mhlw.go.jp/stf/seisakunitsuite/bunya/0000164708_00001.html'
    QUERY_HEADERS = {
        'User-Agent': 'Mozilla/5.0',
    }

    request = urllib.request.Request(CRAWL_URL, headers=QUERY_HEADERS)
    with urllib.request.urlopen(request) as url:
        dom = url.read().decode()

    pdf_url = re.search(r'<a [^>]*href="([^"]+)">国内の入退院の状況について[^<]*</a>', dom).group(1)
    df = tabula.read_pdf(pdf_url, lattice=True)
    if isinstance(df, list):
        df = df[0]

    number_pattern = re.compile('([0-9]+)\(\+([0-9]+)\)')
    nums = []
    for i in range(len(df)):
        nums = []
        for val in df.iloc[i].values:
            m = number_pattern.search(str(val))
            if m is None:
                break
            nums.append((int(m.group(1)), int(m.group(2))))
        else:
            break
    assert len(nums) == 4

    return nums[0], nums[2], nums[3]


def update_cases_recovered_deaths(bucket):
    try:
        print('Getting overall data from MHLW')
        (total_cases, total_cases_changes), (discharged, discharged_changes), (death, death_changes) = get_data_from_mhlw()
        print(f'Queried data successfully')
        storage_ref = f'overall.json'
        blob = bucket.blob(storage_ref)
        blob.upload_from_string(json.dumps({
            'total_cases': total_cases,
            'total_cases_changes': total_cases_changes,
            'discharged': discharged,
            'discharged_changes': discharged_changes,
            'death': death,
            'death_changes': death_changes
        }), content_type='application/json')
        print(f'Uploaded JSON to Firebase storage')
    except Exception as e:
        print('Failed to crawl data from MHLW')
        traceback.print_exc()


def update_clinic(bucket):
    for pref in localization.PREFECTURES.values():
        dataset = ClinicDataset(
            f'clinics/tabula-{pref.lower()}.csv',
            f'clinic-{pref.lower()}',
        )
        print(f'Dataset: {dataset.name}')
        dataset.query_all()
        print(f'Queried data successfully')
        dataset.upload_to_storage(bucket)
        print(f'Uploaded JSON to Firebase storage')
        print('-'*20)


def update_detailed_data(bucket):
    all_datasets = (
        TokyoPatientsDataset(),
        PrefectureByDateDataset(),
        # PatientDetailsDataset(),
        PatientByCityTokyoDataset(),
        PatientByCityOsakaDataset(),
        PatientByCitySaitamaDataset(),
        PatientByCityKanagawaDataset(encoding='cp932'),
    )

    for dataset in all_datasets:
        try:
            print(f'Dataset: {dataset.name}')
            dataset.query_all()
            print(f'Queried data successfully')
            # dataset.save_csv()
            # print(f'Created local CSV file')
            dataset.upload_to_storage(bucket)
            print(f'Uploaded JSON to Firebase storage')
            print('-'*20)
        except Exception:
            print(f'Failed to get dataset {dataset.name}')
            traceback.print_exc()


def main(args=None):
    app, client, bucket = init_firebase_app()
    update_cases_recovered_deaths(bucket)
    print('-' * 20)
    # update_clinic(bucket)
    update_detailed_data(bucket)

    return 0


if __name__ == '__main__':
    sys.exit(main())
