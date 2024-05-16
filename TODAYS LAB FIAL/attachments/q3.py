from math import sqrt
from pathlib import Path

def galMul(x,y):
    product=0
    for _ in range(8):
        if y&1==1:
            product^=x
        highBitSet=x & 0x80
        x<<=1
        if highBitSet==0x80:
            x^=0x1b
        y>>=1
    return product & 0xff

def MixColumn(state):
    it=4
    resultMatrix=[None]*(it*it)
    for i in range(it):
        resultMatrix[4*i+0]=galMul(state[4*i+0],2)^state[4*i+3]^state[4*i+2]^galMul(state[4*i+1],3)
        resultMatrix[4*i+1]=galMul(state[4*i+1],2)^state[4*i+0]^state[4*i+3]^galMul(state[4*i+2],3)
        resultMatrix[4*i+2]=galMul(state[4*i+2],2)^state[4*i+1]^state[4*i+0]^galMul(state[4*i+3],3)
        resultMatrix[4*i+3]=galMul(state[4*i+3],2)^state[4*i+2]^state[4*i+1]^galMul(state[4*i+0],3)
    return resultMatrix

def main():
    with open(Path(__file__).parent/'Input.txt',"r") as file:
        data=file.read()
    data=data[0:16]
    print(data)
    data=[ord(i) for i in data]
    newdata=MixColumn(data)
    print(''.join(chr(i) for i in newdata))

if __name__=='__main__':
    main()