import sys

import firebase_admin
from firebase_admin import credentials, firestore, storage
import pandas as pd

import datasets


PREFECTURES = {
    '北海道': 'Hokkaido',
    '青森県': 'Aomori',
    '岩手県': 'Iwate',
    '宮城県': 'Miyagi',
    '秋田県': 'Akita',
    '山形県': 'Yamagata',
    '福島県': 'Fukushima',
    '茨城県': 'Ibaraki',
    '栃木県': 'Tochigi',
    '群馬県': 'Gunma',
    '埼玉県': 'Saitama',
    '千葉県': 'Chiba',
    '東京都': 'Tokyo',
    '神奈川県': 'Kanagawa',
    '新潟県': 'Niigata',
    '富山県': 'Toyama',
    '石川県': 'Ishikawa',
    '福井県': 'Fukui',
    '山梨県': 'Yamanashi',
    '長野県': 'Nagano',
    '岐阜県': 'Gifu',
    '静岡県': 'Shizuoka',
    '愛知県': 'Aichi',
    '三重県': 'Mie',
    '滋賀県': 'Shiga',
    '京都府': 'Kyoto',
    '大阪府': 'Osaka',
    '兵庫県': 'Hyogo',
    '奈良県': 'Nara',
    '和歌山県': 'Wakayama',
    '鳥取県': 'Tottori',
    '島根県': 'Shimane',
    '岡山県': 'Okayama',
    '広島県': 'Hiroshima',
    '山口県': 'Yamaguchi',
    '徳島県': 'Tokushima',
    '香川県': 'Kagawa',
    '愛媛県': 'Ehime',
    '高知県': 'Kochi',
    '福岡県': 'Fukuoka',
    '佐賀県': 'Saga',
    '長崎県': 'Nagasaki',
    '熊本県': 'Kumamoto',
    '大分県': 'Oita',
    '宮崎県': 'Miyazaki',
    '鹿児島県': 'Kagoshima',
    '沖縄県': 'Okinawa',
}

TOKYO_CITIES = {
    '千代田区': 'Chiyoda',
    '中央区': 'Chuo',
    '港区': 'Minato',
    '新宿区': 'Shinjuku',
    '文京区': 'Bunkyo',
    '台東区': 'Taito',
    '墨田区': 'Sumida',
    '江東区': 'Koto',
    '品川区': 'Shinagawa',
    '目黒区': 'Meguro',
    '大田区': 'Ota',
    '世田谷区': 'Setagaya',
    '渋谷区': 'Shibuya',
    '中野区': 'Nakano',
    '杉並区': 'Suginami',
    '豊島区': 'Toshima',
    '北区': 'Kita',
    '荒川区': 'Arakawa',
    '板橋区': 'Itabashi',
    '練馬区': 'Nerima',
    '足立区': 'Adachi',
    '葛飾区': 'Katsushika',
    '江戸川区': 'Edogawa',
    '八王子市': 'Hachioji',
    '立川市': 'Tachikawa',
    '武蔵野市': 'Musashino',
    '三鷹市': 'Mitaka',
    '青梅市': 'Ome',
    '府中市': 'Fuchu',
    '昭島市': 'Akishima',
    '調布市': 'Chofu',
    '町田市': 'Machida',
    '小金井市': 'Kogane',
    '小平市': 'Kodaira',
    '日野市': 'Hino',
    '東村山市': 'Higashimurayama',
    '国分寺市': 'Kokubunji',
    '国立市': 'Kunitachi',
    '福生市': 'Fussa',
    '狛江市': 'Komae',
    '東大和市': 'Higashiyamato',
    '清瀬市': 'Kiyose',
    '東久留米市': 'Higashikurume',
    '武蔵村山市': 'Musashimurayama',
    '多摩市': 'Tama',
    '稲城市': 'Inagi',
    '羽村市': 'Hamura',
    'あきる野市': 'Akiruno',
    '西東京市': 'Nishitokyo',
    '瑞穂町': 'Thị trấn Mizuho',
    '日の出町': 'Thị trấn Hinode',
    '檜原村': 'Làng Hinohara',
    '奥多摩町': 'Thị trấn Okutama',
    '大島町': 'Đảo Oshima',
    '利島村': 'Đảo Toshima',
    '新島村': 'Đảo Nijima',
    '神津島村': 'Đảo Kozushima',
    '三宅村': 'Đảo Miyake',
    '御蔵島村': 'Đảo Mikurajima',
    '八丈町': 'Đảo Hachijo',
    '青ヶ島村': 'Đảo Aogashima',
    '小笠原村': 'Đảo Ogasawara',
}

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

    def __init__(self):
        super().__init__(self.URL, self.NAME)

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
            **PREFECTURES,
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
    COL_TOTAL =  'Tổng'

    def __init__(self):
        super().__init__(self.URL, self.NAME)

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
        self.dataframe[self.COL_PREFECTURE].replace(PREFECTURES, inplace=True)
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

    def __init__(self):
        super().__init__(self.URL, self.NAME)

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

    def __init__(self):
        super().__init__(self.URL, self.NAME)

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
            **TOKYO_CITIES,
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


def init_firebase_app():
    cred = credentials.Certificate(FIREBASE_PRIVATE_KEY)
    app = firebase_admin.initialize_app(cred, {
        'storageBucket': f'{FIREBASE_APP_NAME}.appspot.com'
    })
    client = firestore.client()
    bucket = storage.bucket(app=app)

    return app, client, bucket


def main(args=None):
    app, client, bucket = init_firebase_app()

    all_datasets = (
        TokyoPatientsDataset(),
        PrefectureByDateDataset(),
        PatientDetailsDataset()
    )

    for dataset in all_datasets:
        print(f'Dataset: {dataset.name}')
        dataset.query_all()
        print(f'Queried data successfully')
        dataset.save_csv()
        print(f'Created local CSV file')
        dataset.upload_to_storage(bucket)
        print(f'Uploaded JSON to Firebase storage')

    return 0

if __name__ == '__main__':
    sys.exit(main())
