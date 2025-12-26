from os import system

from pprint import pprint

def getLineArray(message: str) -> list[str]:
    return message.split("\n")

def exec(command: str) -> str:
    result = ""

    system(f"{command} 1>out.txt")

    with open("out.txt", "r") as f:
        result = f.read()

    return result

if __name__ == "__main__":
    pprint(getLineArray(exec("where /R D:\\Projects\\RandomOS_Boosted *.c *.h *.n *.s")))