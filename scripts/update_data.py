import datetime
import json
import urllib.request
import sys

import firebase_admin
from firebase_admin import credentials, firestore, storage
import pandas as pd


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

DB_PATIENT_ALL = 'patient-all'
DB_PATIENT_TOKYO = 'patient-tokyo'
DB_PREFECTURE_BY_DATE = 'prefecture-by-date'

FIREBASE_APP_NAME = 'thongtincovid19-4dd12'
FIREBASE_BATCH_SIZE = 499  # Max = 500
FIREBASE_PRIVATE_KEY = './thongtincovid19_serviceaccount_privatekey.json'
FIREBASE_STORAGE_BUCKET = 'gs://thongtincovid19-4dd12.appspot.com'


def get_and_cleanse_tokyo_data(auto_drop: bool = False) -> pd.DataFrame:
    """Get data from Tokyo Metropolitan Government and localize to Vietnamese.
    
    Args:
        auto_drop (bool): If True, drop all columns with less than 2 unique values.
    Returns:
        A `pandas.DataFrame` object containing clean data.
    """
    DATA_TOKYO = 'https://stopcovid19.metro.tokyo.lg.jp/data/130001_tokyo_covid19_patients.csv'
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
    
    tokyo_data = pd.read_csv(DATA_TOKYO)
    
    # Localize column name
    tokyo_data.columns = [
        COL_NO,
        COL_AREA_CODE,
        COL_PREFECTURE,
        COL_DISTRICT,
        COL_PUBLISHED_DATE,
        COL_DOW,
        COL_SYMPTOM_DATE,
        COL_PATIENT_ADDRESS,
        COL_PATIENT_AGE,
        COL_PATIENT_SEX,
        COL_PATIENT_ATTRIBUTE,
        COL_PATIENT_STATE,
        COL_PATIENT_SYMPTOM,
        COL_PATIENT_TRAVEL,
        COL_REF,
        COL_DISCHARGED,
    ]
    
    # Localize data
    tokyo_data[COL_PREFECTURE].replace({
        '東京都': 'Tokyo'
    }, inplace=True)
    tokyo_data[COL_DOW].replace({
        '日': 'CN',
        '月': '2',
        '火': '3',
        '水': '4',
        '木': '5',
        '金': '6',
        '土': '7',
    }, inplace=True)
    tokyo_data[COL_PATIENT_ADDRESS].replace({
        '湖北省武漢市': 'Vũ Hán, Hồ Bắc',
        '湖南省長沙市': 'Trường Sa, Hồ Nam',
        '都内': 'Nội đô Tokyo',
        '都外': 'Ngoài Tokyo',
        '調査中': 'Đang điều tra',
        **PREFECTURES,
    }, inplace=True)
    tokyo_data[COL_PATIENT_SEX].replace({
        '男性': 'Nam',
        '女性': 'Nữ',
        '不明': 'Không rõ',
        '調査中': 'Đang điều tra',
    }, inplace=True)
    tokyo_data[COL_PATIENT_AGE] = tokyo_data[COL_PATIENT_AGE].str.replace('代', 's')
    tokyo_data[COL_PATIENT_AGE].replace({
        '10歳未': 'Dưới 10',
        '100歳以': 'Trên 100',
        '不': 'Không rõ',
    }, inplace=True)
    
    # Fill missing data
    tokyo_data[COL_PATIENT_ADDRESS].fillna('―', inplace=True)
    
    if auto_drop:
        # Drop meaningless columns (less than 1 unique value)
        tokyo_data.drop(columns=[
            COL_AREA_CODE,
            COL_PREFECTURE,
            COL_DISTRICT,
            COL_SYMPTOM_DATE,
            COL_PATIENT_ATTRIBUTE,
            COL_PATIENT_STATE,
            COL_PATIENT_SYMPTOM,
            COL_PATIENT_TRAVEL,
            COL_REF,
            COL_DISCHARGED,
        ], inplace=True)
    
    return tokyo_data


def get_and_cleanse_prefecture_data() -> pd.DataFrame:
    """Get data from NHK and localize to Vietnamese."""
    request = urllib.request.Request(
        'https://www3.nhk.or.jp/news/special/coronavirus/data/47newpatients-data.json',
        headers={'User-Agent': 'Mozilla/5.0'}
    )
    with urllib.request.urlopen(request) as url:
        data = json.loads(url.read().decode())

    formatted_list = []
    for pref in data['data47']:
        formatted_list.append([pref['name']] + pref['data'] + [sum(pref['data'])])
    df = pd.DataFrame(formatted_list, columns=['Prefecture'] + data['category'] + ['Total'])
    df['Prefecture'].replace(PREFECTURES, inplace=True)

    return df


def load_patient_database() -> pd.DataFrame:
    """Get data from ArcGIS."""
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
    request = urllib.request.Request(URL, headers={'User-Agent': 'Mozilla/5.0'})
    with urllib.request.urlopen(request) as url:
        data = json.loads(url.read().decode())

    df = pd.DataFrame([entry['attributes'] for entry in data['features']])
    df['Date'].fillna(0, inplace=True)
    df['Date'] = pd.to_datetime(df['Date'], unit='ms')
    df['Date'] = df['Date'].dt.strftime('%Y%m%d %H:%M')
    return df


def batch_data(iterable, n=1):
    """Divide data into batches of fix length."""
    l = len(iterable)
    for ndx in range(0, l, n):
        yield iterable[ndx:min(ndx + n, l)]


def upload_to_firebase(data, client, root, item_key=None, batch_size=FIREBASE_BATCH_SIZE):
    if item_key not in data.columns:
        item_key = None
    data_dict = data.to_dict(orient='record')
    for batched_data in batch_data(data_dict, batch_size):
        batch = client.batch()
        for data_item in batched_data:
            if item_key is not None:
                doc_ref = client.collection(root).document(str(data_item[item_key]))
            else:
                doc_ref = client.collection(root).document()
            batch.set(doc_ref, data_item)
        batch.commit()


def upload_to_storage(data, file_name, bucket):
    """Upload a Dataframe as JSON to Firebase Storage.

    returns
        storage_ref
    """
    storage_ref = file_name + '.json'
    blob = bucket.blob(storage_ref)
    blob.upload_from_string(json.dumps(data.to_dict(orient='record')))

    return storage_ref


def main(args=None):
    cred = credentials.Certificate(FIREBASE_PRIVATE_KEY)
    app = firebase_admin.initialize_app(cred,  {
        'storageBucket': f'{FIREBASE_APP_NAME}.appspot.com'
    })
    client = firestore.client()
    bucket = storage.bucket(app=app)

    tokyo_data = get_and_cleanse_tokyo_data()
    patients_by_prefecture = get_and_cleanse_prefecture_data()
    patients_all = load_patient_database()

    now = datetime.datetime.now()
    timestamp = now.strftime('%Y%m%d_%H%M')
    params = (
        # DataFrame              DB name                Key column
        (tokyo_data,             DB_PATIENT_TOKYO,      'STT'),
        (patients_by_prefecture, DB_PREFECTURE_BY_DATE, 'Prefecture'),
        (patients_all,           DB_PATIENT_ALL,        'ObjectId'),
    )

    for data, db_name, key_column in params:
        print(f'Uploading {db_name}, key_column={key_column}')
        data.to_csv(f'{timestamp}_{db_name}.csv', index=False)
        # upload_to_firebase(data, client, db_name, key_column)
        upload_to_storage(data, db_name, bucket)
    
    return 0

if __name__ == '__main__':
    sys.exit(main())
