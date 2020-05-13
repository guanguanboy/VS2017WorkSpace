#include <alibabacloud/oss/OssClient.h>
#include <fstream>

using namespace AlibabaCloud::OSS;

int main(void)
{
	/* 初始化OSS账号信息 */
	std::string AccessKeyId = "LTAI5KUm6h4lyNL0";
	std::string AccessKeySecret = "NQV4kGThHYDDeyAZ56KMdODL1MaEIy";
	std::string Endpoint = "http://oss-cn-shenzhen.aliyuncs.com";
	std::string BucketName = "obscanner";
	/* yourObjectName表示上传文件到OSS时需要指定包含文件后缀在内的完整路径，例如abc/efg/123.jpg*/
	std::string ObjectName = "3dmodel/total_aligned_recon_clean.drc";

	/* 初始化网络等资源 */
	InitializeSdk();

	ClientConfiguration conf;
	OssClient client(Endpoint, AccessKeyId, AccessKeySecret, conf);

	///* 指定新创建bucket的名称、存储类型和ACL */
	//CreateBucketRequest request(BucketName, StorageClass::IA, CannedAccessControlList::PublicReadWrite);

	///* 创建bucket */
	//auto outcome = client.CreateBucket(request);
	std::shared_ptr<std::iostream> content = std::make_shared<std::fstream>("E:/VS2017WorkSpace/alibabacloud_oss_test/x64/Debug/total_aligned_recon_clean.drc", std::ios::in | std::ios::binary);
	PutObjectRequest request(BucketName, ObjectName, content);

	auto outcome = client.PutObject(request);

	if (!outcome.isSuccess()) {
		/* 异常处理 */
		std::cout << "CreateBucket fail" <<
			",code:" << outcome.error().Code() <<
			",message:" << outcome.error().Message() <<
			",requestId:" << outcome.error().RequestId() << std::endl;
		ShutdownSdk();
		return -1;
	}

	/* 判断文件是否存在 */
	auto outcome1 = client.DoesObjectExist(BucketName, ObjectName);

	if (outcome1) {
		std::cout << "The Object exists!" << std::endl;
	}
	else {
		std::cout << "The Object does not exist!" << std::endl;
	}

	/* 释放网络等资源 */
	ShutdownSdk();
	return 0;
}