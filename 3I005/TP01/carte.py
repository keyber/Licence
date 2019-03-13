import random

def paquet():
    l=[]
    for couleur in ("C","K","P","T"):
        for i in range (13):
            l.append((couleur, i))
    return l
    
def memePos(p,q):
    l=[]
    for i in range(52):
        if p[i]==q[i]:
            l.append(i)
    return l

def main():
    p=paquet()
    q=paquet()
    with open("log", "w") as f:
        som=0.0
        for i in range (1,1000):
            random.shuffle(p)
            random.shuffle(q)
            nb=len(memePos(p,q))
            som+=nb
            f.write(str(i) + " " + str(som/i) + "\n")
main()
        
        
        
    
    
