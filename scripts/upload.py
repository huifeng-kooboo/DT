# -*- coding=utf-8
# appid 已在配置中移除,请在参数 Bucket 中带上 appid。Bucket 由 BucketName-APPID 组成
# 1. 设置用户配置, 包括 secretId，secretKey 以及 Region
from qcloud_cos import CosConfig
from qcloud_cos import CosS3Client

__all__ = {'cos_upload_file'}

# 此处的配置信息 需要去申请腾讯云cos服务中获取
TX_COS_BUCKET_NAME = "xxxxx"
TX_COS_REGION = 'xxxx'
TX_COS_SECRETID = 'xxx'
TX_COS_SECRETKEY = 'xxx'

secret_id = TX_COS_SECRETID  # 替换为用户的 secretId
secret_key = TX_COS_SECRETKEY  # 替换为用户的 secretKey
region = TX_COS_REGION  # 替换为用户的 Region

token = None  # 使用临时密钥需要传入 Token，默认为空，可不填
scheme = 'https'  # 指定使用 http/https 协议来访问 COS，默认为 https，可不填
config = CosConfig(Region=region,
                   SecretId=secret_id,
                   SecretKey=secret_key,
                   Token=token,
                   Scheme=scheme)
# 2. 获取客户端对象
client = CosS3Client(config)


def cos_upload_file(file_name, key_name=""):
    """
    上传文件接口:
    return url:文件下载地址
    """
    if key_name == "":
        key_name = file_name
    client.upload_file(
        Bucket=TX_COS_BUCKET_NAME,
        LocalFilePath=file_name,  # 本地文件的路径
        Key=key_name,  # 上传到桶之后的文件名
        PartSize=1,  # 上传分成几部分
        MAXThread=10,  # 支持最多的线程数
        EnableMD5=False  # 是否支持MD5
    )
    url = client.get_object_url(Bucket=TX_COS_BUCKET_NAME, Key=key_name)
    return url