from random import randrange
 
def hyphenate(kelime):
    def unlumu(kelime):
        uzunluk = len(kelime)
        unluler = ["a","e","o","u","i","I","U","O"]
        ikili = []
        for i in range(0,uzunluk ):
            if kelime[i] in unluler:
                ikili.append(1)
            else:
                ikili.append(0)
        return ikili        
 
 
    def hecele(kelime):
        uzunluk = len(kelime)
        kelimeunlumu = unlumu(kelime)
        bir = 0
        for i in range(0,uzunluk):
            if kelimeunlumu[i] == 1:
                bir += 1
 
        if bir == 1:
            return [kelime]
 
        if uzunluk == 0:
            return []
         
        else:
            if uzunluk <= 2:
                return [kelime]
            if uzunluk >= 3:
                if uzunluk == 3:
                    if kelimeunlumu[-1] == 0 and kelimeunlumu[-2] == 1 and kelimeunlumu[-3] == 0:
                        return [kelime]
                    if kelimeunlumu[-1] == 1 and kelimeunlumu[-2] == 0 and kelimeunlumu[-3] == 0:
                        return [kelime] 
                    if kelimeunlumu[-1] == 0 and kelimeunlumu[-2] == 0 and kelimeunlumu[-3] == 1:
                        return [kelime]
                if kelimeunlumu[-1] == 1 and kelimeunlumu[-2] == 0 and kelimeunlumu[-3] == 1:
                    return [kelime[-2:]] + hecele(kelime[:-2])
                if uzunluk >= 4:
                    if kelimeunlumu[-1] == 1:
                         
 
                        if kelimeunlumu[-2] == 0 and kelimeunlumu[-3] == 0 and kelimeunlumu[-4] == 1:
                            return [kelime[-2:]] +  hecele(kelime[:-2])
 
 
                    if kelimeunlumu[-1] == 0:
                        if kelimeunlumu[-2] == 1 and kelimeunlumu[-3] == 0 and kelimeunlumu[-4] == 1:
                            return [kelime[-3:]] + hecele(kelime[:-3])
                        if kelimeunlumu[-2] == 1 and kelimeunlumu[-3] == 1 :
                            return [kelime[-2:]] + hecele(kelime[:-2])
                         
 
                                 
                    if uzunluk >= 5:
                        if kelimeunlumu[-1] == 1:
                            if kelimeunlumu[-2] == 0 and kelimeunlumu[-3] == 0 and kelimeunlumu[-4] == 0 and kelimeunlumu[-5] == 1:
                                if kelime[-3] == "r":
                                    return [kelime[-3:]] + hecele(kelime[:-3])
                                return [kelime[-2:]] + hecele(kelime[:-2])
                        if kelimeunlumu[-1] == 0:
                            if kelimeunlumu[-2] == 1 and kelimeunlumu[-3] == 0 and kelimeunlumu[-4] == 0 and kelimeunlumu[-5] == 1: 
                                return [kelime[-3:]] + hecele(kelime[:-3])
                            if kelimeunlumu[-2] == 0 and kelimeunlumu[-3] == 1 and kelimeunlumu[-4] == 0 and kelimeunlumu[-5] == 1:
                                return [kelime[-4:]]    + hecele(kelime[:-4])
 
                        if uzunluk >= 6:
                            if kelimeunlumu[-1] == 1 and kelimeunlumu[-2] == 0 and kelimeunlumu[-3] == 0 and kelimeunlumu[-4] == 0 and kelimeunlumu[-5] == 0 and kelimeunlumu[-6] == 1:
                                if kelime[-3] == "r":
                                    return [kelime[-2:]] + hecele(kelime[:-2])
                                return [kelime[-3:]] + hecele(kelime[:-3])
                            if kelimeunlumu[-1] == 0 and kelimeunlumu[-2] == 1 and kelimeunlumu[-3] == 0 and kelimeunlumu[-4] == 0 and kelimeunlumu[-5] == 0 and kelimeunlumu[-6] == 1: 
                                if kelime[-4] == "r":
                                    return [kelime[-4:]] + hecele(kelime[:-4])
                                return [kelime[-3:]] + hecele(kelime[:-3])
                            if uzunluk >= 7:
                                if kelimeunlumu[-1] == 1 and kelimeunlumu[-2] == 0 and kelimeunlumu[-3] == 0 and kelimeunlumu[-4] == 0 and kelimeunlumu[-5] == 0 and kelimeunlumu[-6] == 0:
                                    return [kelime[-3:]] + hecele(kelime[:-3])
 
 
    heceli = hecele(kelime)
    heceli = heceli[::-1]
    return heceli
 
 
 
 
 
 
 
 
 
def execute():
    a = raw_input()
    if " " in a:
        sayilar = a.split(" ")
    if "," in a:
        sayilar = a.split(",")
 
    sayilar = [int(sayilar[0]),int(sayilar[1])]
    n = sayilar[0]
    m = sayilar[1]
 
    paragraf = "" 
 
    while True:
 
        lin = raw_input()
         
 
        if lin == "=":
            break
 
        if paragraf == "":
                    paragraf = paragraf +  lin
                    continue
                         
        if paragraf != "":  
            if paragraf[-1] == ".":
                paragraf = paragraf + lin
 
            else:
                paragraf = paragraf + " " + lin 
 
 
 
 
    def paragrafhecele(paragraf): #verilen paragrafi heceli bir paragraf olarak doner
         
        cumleler = paragraf.split(".")
        if cumleler[-1] == "":
            del cumleler[-1]
        cumlesayisi = len(cumleler)
        kelimeler = []
        heceliparagraf = []
         
        for i in range(0,cumlesayisi):
            kelimeler.append(cumleler[i].split(" "))
        for i in range(0,len(kelimeler)):
 
            for j in range(0,len(kelimeler[i])):
                heceli = hyphenate(kelimeler[i][j])
                 
                heceliparagraf.extend(heceli)
 
                heceliparagraf.append(" ")
            del heceliparagraf[-1]  
            heceliparagraf.append(".")
 
 
        return heceliparagraf           
 
 
    def kelimeilkharf(paragraf):
        ilkheceler = [paragraf[0]]
        uzunluk = len(paragraf)
        for i in range(1,uzunluk):
            if paragraf[i-1] == " " or paragraf[i-1] == ".":
                ilkheceler.append(paragraf[i])
        return ilkheceler
 
 
 
 
 
    def encok(paragraf,hece):# burda bize rastgele gelen heceden sonraki hangi hece nekadar geciyor onu hesapladik
        uzunluk = len(paragraf)
        liste = []
        for i in range(0,uzunluk):
            if paragraf[i] == hece:
                hece2 = paragraf[i+1]
                tekrar = 0
                for j in range(0,uzunluk):
                    if paragraf[j] == hece and paragraf[j+1] == hece2:
                        tekrar += 1
                sirali = [hece2,tekrar]
                if sirali not in liste:
                    liste.append(sirali)
        if len(liste) == 0:
            return " "
 
        if len(liste) == 1:
            return liste[0][0]
 
        else:
            tut1 = liste[0]
            konum = 0
            for i in range(0,len(liste)):
                if liste[i][1] > tut1[1]:
                    tut1 = liste[i]
                    konum = i
            del liste[konum]
            tut2 = liste[0]
            konum2 = 0
            for j in range(0,len(liste)):
                if liste[j][1] > tut2:
                    tut2 = liste[j]
                    konum2 = j
            liste = [tut1,tut2]
            sec  = randrange(0,2)
            return liste[sec][0]
                     
 
 
    def output(n,m,ilkheceler,paragrafheceli):  
                     
        yeniparagraf = ""
 
        for i in range(0,n):
            if len(paragrafhecele(yeniparagraf)) >= m:
                break
            kelimesayisi = len(ilkheceler)
            rastgelehecekonum = randrange(0, kelimesayisi )###########
            rastgelehece = ilkheceler[rastgelehecekonum]
            yeniparagraf = yeniparagraf + rastgelehece
            while  True:
                hece = encok(paragrafheceli,rastgelehece)
                if hece == " ":
                    yeniparagraf = yeniparagraf + " "
                    break
                if hece == ".":
                    yeniparagraf = yeniparagraf + "."
                    break
                yeniparagraf = yeniparagraf + hece
                rastgelehece = hece
        if yeniparagraf[-1] != ".":
            yeniparagraf = yeniparagraf[:-1] + "."     
        return yeniparagraf
 
             
 
 
 
 
 
 
 
 
 
 
 
 
 
 
    paragrafheceli = paragrafhecele(paragraf)
    ilkheceler = kelimeilkharf(paragrafheceli)
 
    outputum = output(n,m,ilkheceler,paragrafheceli)
 
 
 
 
 
 
 
    #print paragraf
    #print"|"
    #print"|"
    #print paragrafheceli
    #print"|"
    #print"|"
    #print ilkheceler
    #print"|"
    #print"|"
    print outputum
