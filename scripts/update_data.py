import datetime
import sys

import pandas as pd

def get_and_cleanse_tokyo_data(auto_drop: bool = False) -> pd.DataFrame:
    """Get data from Toyko Metropolitan Government and localize to Vietnamese.
    
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
        '埼玉県': 'Saitama',
        '都外': 'Ngoài Tokyo',
        '調査中': 'Đang điều tra',
    }, inplace=True)
    tokyo_data[COL_PATIENT_SEX].replace({
        '男性': 'Nam',
        '女性': 'Nữ',
        '不明': 'Không rõ',
        '調査中': 'Đang điều tra',
    }, inplace=True)
    tokyo_data[COL_PATIENT_AGE] = tokyo_data[COL_PATIENT_AGE].apply(lambda x: x[:-1])  # Remove 代 at the end of age
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


def main(args=None):
    tokyo_data = get_and_cleanse_tokyo_data()
    
    now = datetime.datetime.now()
    timestamp = now.strftime('%Y%m%d_%H%M')
    file_names = ['tokyo']
    for file_name, data in zip(file_names, [tokyo_data]):
        data.to_csv(f'{timestamp}_{file_name}.csv', index=False)
    
    return 0

if __name__ == '__main__':
    sys.exit(main())
