from PIL import Image

im1 = Image.open("./01.jpg")
im2 = Image.open("./02.jpg")

box=[0,0,1440,900]
region = im2.crop(box)

out = Image.blend(im1, region, 0.8)
im2.paste(out)

im2.show()
