from PIL import Image, ImageDraw

from pyperclip import copy

rus_img = Image.open("rus.gif").convert("RGB")

rus_big_img = Image.open("rusbig.gif").convert("RGB")

width, height = rus_img.size

rus_img_pixs = list(rus_img.getdata())

rus_big_img_pixs = list(rus_img.getdata())

rus_draw = ImageDraw.Draw(rus_img)

rus_big_draw = ImageDraw.Draw(rus_big_img)

result_rus = ""

result_rus_big = ""

num = 0

for sx in range(0, width, 9):
	result_rus += "{ "

	result_rus_big += "{ "

	for y in range(16):
		result_rus += "0b"

		result_rus_big += "0b"

		for x in range(8):
			if (rus_img_pixs[sx + x + (y * width)] == (0, 0, 0)):
				result_rus += "1"

			else: result_rus += "0"

			if (rus_big_img_pixs[sx + x + (y * width)] == (0, 0, 0)):
				result_rus_big += "1"

			else: result_rus_big += "0"

		if (y != 15):
			result_rus += ","

			result_rus_big += ","

		result_rus += "\n"

		result_rus_big += "\n"

	result_rus += " }"

	result_rus_big += " }"

	if (num < 33):
		result_rus += ","

		result_rus_big += ","

	result_rus += "\n"

	result_rus_big += "\n"

	if (num >= 33):
		break

	num += 1

	rus_draw.point((sx, 0), (255, 0, 0))

	rus_draw.point((sx + 8, 15), (0, 255, 0))

	rus_big_draw.point((sx, 0), (255, 0, 0))

	rus_big_draw.point((sx + 8, 15), (0, 255, 0))

with open("rus.charset", mode="w") as f:
	f.write(result_rus)

with open("rus_big.charset", mode="w") as f:
	f.write(result_rus_big)

rus_img.show()

rus_big_img.show()