# 训练

## 简介  
    此目录主要保存训练SVM分类器的文件
    目录结构
- dataset 数据集
	|---- create_file_list.sh 生成数据集文件列表文件的脚本  
	|---- neg 负样本，64×128  
	|---- pos 正样本，宽高比为1：2的图片，或者是96×160像素的图像  
	|---- neg_ori 原始负样本，尺寸大于64×128  
	|---- 根据neg和第一遍训练结果生成的难例  
	|---- rename-photo.sh 对目录内图片进行批量重命名的脚本  
- source 训练代码  
	|---- train.cpp  训练代码
	|---- find_save_HardExample.cpp 生成难例的代码  
	|---- dataset.h  主要保存数据集路径，数量等的信息  
	|---- Test.jpg  测试用的图片
	|---- crop_image.cpp 生成负样本的程序  
	|---- trainimgExample_positice.7z matlab裁剪正样本的辅助程序

## 使用方法
- 先将正样本保存在dataset目录的pos中（图像尺寸有要求）
- 将原始负样本保存在dataset目录下的neg_ori中  
- 然后在source目录下make  
- 用source生成的crop_image裁剪出负样本  
- 用source下的train训练正负样本  
- 用source下的creat_hard_example生成难例  
- 重新训练  

具体训练效果需要自己把握

