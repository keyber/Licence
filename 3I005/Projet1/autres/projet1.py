import email
import re
import math
import numpy as np
import matplotlib.pyplot as plt


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
    mails = read_file(f)
    return [s for s in
             [clean_body(get_body(email.message_from_bytes(x))) for x in mails]
            if s !=""]

def splitList (liste, x):
    limite = len(liste)*x//100
    return (liste[:limite], liste[limite:])



taille_max = 10000
def taille_consideree(taille):
    #considere tous les paquets de plus de taille_max lettres comme faisant taille_max
    return round(math.sqrt(min(taille, taille_max)))
    #return min(len(s), taille_max)
    
nb_paquet = 20
taille_intervalle = taille_consideree(taille_max)//nb_paquet

def histo_from_list(liste):
    """un histo est un tableau indexe par (longueur message /taille_intervalle)
    contenant la proba (float) qu'un message fasse cette taille"""
    
    #cree histogramme avec bande de largeur taille_intervalle

    histo, _, _= plt.hist([taille_consideree(len(s)) for s in liste],
                          bins=nb_paquet,
                          weights=[1/len(liste)]*len(liste))    #divise par taille totale pour obtenir proba
    
    return histo
    
def apprend_modele(spam, nospam):
    """renvoie un histo pour spam et un pour nospam"""
    return (histo_from_list(spam), histo_from_list(nospam))

def index_dans_hist(s):
    return (taille_consideree(len(s))-1)//taille_intervalle

def predit_email(mail, histSpam ,histNospam):
    """return 1 for spam"""
    index = index_dans_hist(mail)
    if histSpam[index] > histNospam[index] :
        return 1
    return 0

def mainexo2():
    spam = get_emails_from_file("spam.txt" )
    nospam = get_emails_from_file("nospam.txt")
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

        print(pourcentage, 100*(labelS[0]+labelN[1])/(labelS[0]+labelS[1]+labelN[0]+labelN[1]))
        print(labelS, 100*labelS[0]/(labelS[0]+labelS[1]))
        print(labelN, 100*labelN[1]/(labelN[0]+labelN[1]))
    #histo_from_list(spam)
    #plt.show()











"""-------------------------exo3-------------------------"""

        
def mot_apparait(mail, recherche):
    for mot in mail.split(" "):
        if mot == recherche:
            return True
    return False

def compte_mot(liste):
    #dictionnaire comptant pour chaque mot le nombre de mail dans lequel il apparait
    apparition = {}    
    
    #pour chaque mail
    for i in range(len(liste)):
        s = liste[i]

        #pour chacun de ses mots
        for mot in s.split(" "):
            

            #regarde dans les mails suivants si il apparait
            for j in range(i+1, len(liste)):
                autre = liste[j]
                if autre != s and mot_apparait(autre, mot):
                    if mot not in apparition :
                        apparition[mot]=1
                    else :
                        apparition[mot]+=1

    return apparition
                
    
def mainexo3():
    spam = get_emails_from_file("spam.txt")
    spam, rest = splitList (spam, 5)
    d = compte_mot(spam)
    v=[n for n in iter(d.values())]
    """
    print(len(spam), len(v))
    #print(v)
    cpt=0
    for i in v:
        if i==0:
            cpt+=1
    print (cpt, cpt/len(v))"""
    plt.plot(v)
    plt.show()


    


"""
70% des mots apparaissent dans un mail uniquement
ex3 afficher log(proba)
utiliser bibliothèque nltk (stemmer)
rajouter petite proba pour que produit ne soit pas nul"""    


mainexo2()
