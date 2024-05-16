from pathlib import Path
def sha512(message):
    
    #print(message)
    bm=bin(int.from_bytes(message,'big'))
    print(bm)

    lenMessage=len(message)
    message+=b'\x80'
    bm=bin(int.from_bytes(message,'big'))
    print(bm)
    #print(message)

    paddingLength=112-(len(message)%128)
    if paddingLength<0:
        paddingLength+=128  
    message+=b'\x00'*paddingLength
    bm=bin(int.from_bytes(message,'big'))
    #print(message)
    print(bm)

    paddedLen=(lenMessage*8).to_bytes(16,'big') 
    message+=paddedLen
    bm=bin(int.from_bytes(message,'big'))
    print(bm)
    #print(message)


def main():
    with open(Path(__file__).parent/'Input.txt',"r") as file:
        data=file.read()
 
    sha512(bytes(data,'utf-8'))
    

if __name__=='__main__':
    main()