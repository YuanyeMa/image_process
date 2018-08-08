from PIL import Image

im1 = Image.open("./01.jpg")
im2 = Image.open("./02.jpg")

im2 = im2.resize(im1.size)

out = Image.blend(im1,im2, 0.8)

out.show()
