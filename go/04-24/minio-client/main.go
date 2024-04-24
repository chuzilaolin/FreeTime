package main

import (
	"context"
	"log"
	"os"
	"github.com/minio/minio-go/v7"
	"github.com/minio/minio-go/v7/pkg/credentials"
)

// 上传文件
func uploadObject(minioClient *minio.Client, bucketName, objectName, filePath string) (objectURL string, err error) {
    _, err = minioClient.FPutObject(context.Background(), bucketName, objectName, filePath, minio.PutObjectOptions{})
    if err != nil {
        log.Fatalln("文件上传失败:", err.Error())
    }
    return objectURL, nil
}


func main() {
    // 从命令行获取对象名和路径
    args := os.Args[1:]
    objectName := args[0]
    filepath := args[1]

    // minio服务器信息
    endpoint := ""
    accessKeyID := ""
    secretAccessKey := ""
	// useSSL := true
    // 桶信息
    bucket := "54test"

	// Initialize minio client object.
	minioClient, err := minio.New(endpoint, &minio.Options{
		Creds:  credentials.NewStaticV4(accessKeyID, secretAccessKey, ""),
		// Secure: useSSL,
	})
    if err != nil {
        log.Fatalln(err)
    }
    uploadObject(minioClient, bucket, objectName, filepath);

}


