import email
import re
import math
import numpy as np
import matplotlib.pyplot as plt
#from nltk.stem import PorterStemmer

#ps = PorterStemmer()
def tokenize(stringMail):
    """mail -> list<mot>
    simplifie les mots (ex "mots" -> "mot", "simplifie" -> "simplifi") """
    #res = [word for word in [ps.stem(w) for w in stringMail.lower().split(" ")] if len(word)!=0]
    res = [w for w in stringMail.lower().split(" ")if len(w)!=0]
    return res

def compte_mot(liste):
    """list<mail> -> Map<mot, intNbOccurence>
    retourne dictionnaire comptant pour chaque
    mot apparaissant dans au moins deux mails
    le nombre de mail dans lequel il apparait."""
    apparition = {}
    contenu = [frozenset(tokenize(mail)) for mail in liste]
    
    #pour chaque mail
    for ensMotMail in contenu:

        #ajoute tous ses mots
        for mot in ensMotMail:            
            if mot not in apparition :
                apparition[mot]=1
            else :
                apparition[mot]+=1
            
    return apparition


def apprend_modeles(l1, l2):
    """list<mail>**2 -> Map<mot, floatProbaSpam>"""
    m1 = compte_mot(l1)
    m2 = compte_mot(l2)
    
    #fusionne les deux map de nbOccurence en une map de proba
    dic = {}
    
    #pour chaque mot contenu dans les dictionnaires
    for mot in frozenset(m1.keys()).union(m2.keys()):
        n1=epsilon
        n2=epsilon
        if mot in m1:
            n1=m1[mot]
        if mot in m2:
            n2=m2[mot]
        
        #n'ajoute pas les mots apparaissant trop peu de fois
        if n1+n2<nbOccMin:
            continue
            
        #nb spam / nb tot
        p = n1/(n1+n2)
        
        #n'ajoute que les mots qui ont de l'importance
        if abs(p-.5)>seuil:
            dic[mot]=p
            
    return dic


def predit_mail_dict(mail, dic):
    if p_spam(mail, dic)>.5 :
        return 1
    return 0

def p_spam(mail, dic):
    p = 1
    for w in tokenize(mail):
        if w in dic:
            p = p * (1 - dic[w]) / dic[w]
    return 1/(p+1)
    
taille_instance = 1000
seuil=.25
nbOccMin=31
#les mots sont consideres comme appartenant a un semi spam et un demi ham minimum
epsilon=.5

def main():
    spam = get_emails_from_file("spam.txt")
    nospam = get_emails_from_file("nospam.txt")
    print(len(spam), len(nospam))

    dic = apprend_modeles(spam[:taille_instance],nospam[:taille_instance])
    affiche(dic)
    
    labelS = [0,0]
    for mail in spam[taille_instance:]:
        labelS[predit_mail_dict(mail, dic)] += 1
    labelN = [0,0]
    for mail in nospam[taille_instance:]:
        labelN[predit_mail_dict(mail, dic)] += 1
        
    print(100*(labelS[0]+labelN[1])/(labelS[0]+labelS[1]+labelN[0]+labelN[1]), "% d'erreur")
    print(labelS, 100*labelS[0]/(labelS[0]+labelS[1]), "% d'erreur sur les spams")
    print(labelN, 100*labelN[1]/(labelN[0]+labelN[1]), "% d'erreur sur les hams")


def most_used(mod, qte):
    mostUsedWords = []
    for mot in iter(mod.keys()):
        mostUsedWords.append((mot, mod.get(mot)))
    mostUsedWords = sorted(mostUsedWords, key=lambda tup: tup[1], reverse=True)
    for i in range(min(qte, len(mostUsedWords))):
        print(mostUsedWords[i])
        
def most_significant(mod, qte):
    mostUsedWords = []
    for mot in iter(mod.keys()):
        mostUsedWords.append((mot, mod.get(mot)))
    mostUsedWords = sorted(mostUsedWords, key=lambda tup: abs(.5-tup[1]), reverse=True)
    for i in range(min(qte, len(mostUsedWords))):
        print(mostUsedWords[i])
        
def affiche(mod):
    print("taille instance", taille_instance)
    print("seuil", seuil)
    print("nb occ min", nbOccMin)
    print("taille dic", len(mod))
    #most_significant(mod, 9999)
    """
    val = [_ for _ in iter(.values())]
    plt.bar(range(len(val)) , val)
    plt.suptitle('')
    plt.plot(val, '.')
    plt.show()
    plt.close()
    plt.xticks(range(max(val)+1))
    plt.hist(val, bins=max(val))
    plt.show()
    """
    

def read_file(fname):
    """ Lit un fichier compose d'une liste de emails, chacun separe par au moins 2 lignes vides."""
    f = open(fname,'rb')
    raw_file = f.read()
    f.close()
    raw_file = raw_file.replace(b'\r\n',b'\n')
    emails =raw_file.split(b"\n\n\nFrom")
    emails = [emails[0]]+ [b"From"+x for x in emails[1:] ]
    return emails

def get_body(em):
    """ Recupere le corps principal de l'email """
    body = em.get_payload()
    if type(body) == list:
        body = body[0].get_payload()
    try:
        res = str(body)
    except Exception:
        res=""
    return res

def clean_body(s):
    """ Enleve toutes les balises html et tous les caracteres qui ne sont pas des lettres """
    patbal = re.compile('<.*?>',flags = re.S)
    patspace = re.compile('\W+',flags = re.S)
    return re.sub(patspace,' ',re.sub(patbal,'',s))


def get_emails_from_file(f):
    """string -> list<string>"""
    mails = read_file(f)
    return [s for s in
             [clean_body(get_body(email.message_from_bytes(x))) for x in mails]
            if s !=""]

main()

