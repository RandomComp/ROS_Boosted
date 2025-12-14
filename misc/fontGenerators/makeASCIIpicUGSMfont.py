from PIL import Image, ImageDraw

from pyperclip import copy

img = Image.open("ascii.gif").convert("RGB")

width, height = img.size

pixs = list(img.getdata())

draw = ImageDraw.Draw(img)

result = ""

num = 0

for sx in range(88, width, 48):
	for sy in range(25, height - 12, 12):
		if (num >= 12):
			result += "{\n"

			for y in range(12):
				result += " 0b"

				for x in range(8):
					if (pixs[sx + x + ((sy + y) * width)] == (255, 255, 255)):
						result += "1"

					else: result += "0"

				if (y != 11):
					result += ","

				result += "\n"

			result += " }"

			if (num <= 106): result += ","

			result += "\n"

		num += 1

		if (num > 107): break

		draw.point((sx, sy), (255, 0, 0))

		draw.point((sx + 8, sy + 12), (0, 255, 0))

	else: continue

	break

with open("ascii.charset", mode="w") as f:
	f.write(result)

img.show()