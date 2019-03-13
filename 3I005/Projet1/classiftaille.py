import email
import re
import math
import numpy as np
import matplotlib.pyplot as plt


taille_min = 7.4
taille_max = 2980
def taille_consideree(taille):
    #considere tous les paquets de plus de taille_max mots comme faisant taille_max
    return math.log(min(max(taille, taille_min), taille_max-1))
    #return math.log(taille)
    
nb_paquet = 18
taille_intervalle = math.log(taille_max)/nb_paquet

def histo_from_list(liste):
    """un histo est un tableau indexe par (longueur message /taille_intervalle)
    contenant la proba (float) qu'un message fasse cette taille"""
    
    #cree histogramme avec bande de largeur taille_intervalle
    histo, _, _= plt.hist([taille_consideree(len(s)) for s in liste],
                          bins=nb_paquet,
                          #divise par taille totale pour obtenir proba
                          weights=[1/len(liste)]*len(liste))
    plt.show()
    plt.close()
    return histo
    
def apprend_modele(spam, nospam):
    """renvoie un histo pour spam et un pour nospam"""
    return (histo_from_list(spam), histo_from_list(nospam))

def index_dans_hist(s):
    return (int)((taille_consideree(len(s)-1))/taille_intervalle)

def predit_email(mail, histSpam ,histNospam):
    """return 1 for spam"""
    index = index_dans_hist(mail)
    if histSpam[index] > histNospam[index] :
        return 1
    return 0

def main():
    spam = [mail.split(" ") for mail in get_emails_from_file("spam.txt")]
    nospam = [mail.split(" ") for mail in get_emails_from_file("nospam.txt")]

    #plt.plot([len(m) for m in spam+nospam])
    #print(max ([len(m) for m in spam]), len(nospam))
    #histo_from_list(nospam)
    #plt.axis([0000,5000,0,100])
    #plt.show()

    #fait varier le pourcentage de mails utilises pour apprentissage
    for i in range(1,10):
        pourcentage = 10 * i
        apprentissageS, testS = splitList (spam, pourcentage)
        apprentissageN, testN = splitList (nospam, pourcentage)
    
        pS, pN = apprend_modele(apprentissageS, apprentissageN)

        labelS = [0,0]
        for s in testS:
            labelS[predit_email(s,pS,pN)] += 1
        
        labelN = [0,0]
        for s in testN:
            labelN[predit_email(s,pS,pN)] += 1

        print(pourcentage, "% des mails pour l'apprentissage")
        print(100*(labelS[0]+labelN[1])/(labelS[0]+labelS[1]+labelN[0]+labelN[1]), "% d'erreur")
        print(labelS, 100*labelS[0]/(labelS[0]+labelS[1]), "% d'erreur sur les spams")
        print(labelN, 100*labelN[1]/(labelN[0]+labelN[1]), "% d'erreur sur les hams\n")


def get_emails_from_file(f):
    """string -> list<string>"""
    mails = read_file(f)
    return [s for s in
             [clean_body(get_body(email.message_from_bytes(x))) for x in mails]
            if s !=""]

def splitList (liste, x):
    """coupe la liste en deux morceaux de x% et (100-x)%"""
    separation = len(liste)*x//100
    return (liste[:separation], liste[separation:])

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


main()

