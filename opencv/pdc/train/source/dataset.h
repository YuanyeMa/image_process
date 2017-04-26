#ifndef DATASET_H
#define DATASET_H

#define PosSamNO 2663  //正样本个数
#define NegSamNO 12180    //负样本个数

#define PosSamListFile "./../dataset/pos_sample_list.txt" //正样本图片的文件名列表
#define NegSamListFile "./../dataset/neg_sample_list.txt" //负样本图片的文件名列表
#define HardExampleListFile "./../dataset/hard_sample_list.txt"
#define ORI_NegSamListFile "./../dataset/ori_neg_sample_list.txt"

#define POS_SAMPLE_PATH "./../dataset/pos/"
#define NEG_SAMPLE_PATH	"./../dataset/neg/"
#define HARD_SAMPLE_PATH "./../dataset/hard/"
#define NEG_SAMPLE_ORIGIN_PATH "./../dataset/neg_ori/" //原始负样本的路径

#define TRAIN true   //是否进行训练,true表示重新训练，false表示读取xml文件中的SVM模型
#define CENTRAL_CROP true   //true:训练时，对96*160的INRIA正样本图片剪裁出中间的64*128大小人体

//HardExample：负样本个数。如果HardExampleNO大于0，表示处理完初始负样本集后，继续处理HardExample负样本集。
//不使用HardExample时必须设置为0，因为特征向量矩阵和特征类别矩阵的维数初始化时用到这个值
#define HardExampleNO 494

#define TermCriteriaCount 50000  //迭代终止条件，当迭代满50000次或误差小于FLT_EPSILON时停止迭代

#define TestImageFileName "Test.jpg"  //训练完成后读入一张图片来测试效果

#endif
