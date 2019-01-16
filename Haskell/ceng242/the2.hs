import Data.List 
-- YOU MAY USE THIS MODULE FOR SORTING THE AGENTS
data Level = Newbie | Intermediate | Expert deriving (Enum, Eq, Ord, Show, Read)
data Hunter = Hunter {hID::Int, hlevel::Level, hEnergy::Int, hNumberOfCatches::Int, hActions::[Direction]} deriving (Eq, Show, Read)
data Prey = Prey {pID::Int, pEnergy::Int, pActions::[Direction]} deriving (Eq, Show, Read)
data Cell = O | X | H Hunter | P Prey | T deriving (Eq, Show, Read)
data Direction = N | S | E | W deriving (Eq, Show, Read)
type Coordinate = (Int, Int)



-- DO NOT CHANGE THE DEFINITIONS ABOVE. --
-- INSTANCES OF Ord FOR SORTING, UNCOMMENT AND COMPLETE THE IMPLEMENTATIONS --

instance Ord Hunter where
    compare h1 h2 
          | compare (hlevel h1) (hlevel h2) == GT = GT
          | compare (hlevel h1) (hlevel h2) == LT = LT
          | compare (hEnergy h1) (hEnergy h2) == LT = LT
          | compare (hEnergy h1) (hEnergy h2) == GT = GT
          | compare (hNumberOfCatches h1) (hNumberOfCatches h2) == LT = LT
          | compare (hNumberOfCatches h1) (hNumberOfCatches h2) == GT = GT
          | compare (hID h1) (hID h2) == GT = LT
          | compare (hID h1) (hID h2) == LT = GT 

instance Ord Prey where
    compare p1 p2 | compare (pEnergy p1) (pEnergy p2) == GT = GT
      | compare (pEnergy p1) (pEnergy p2) == LT = LT
      | compare (pID p1) (pID p2) == GT = LT
        | compare (pID p1) (pID p2) == LT = GT 
 



 -- WRITE THE REST OF YOUR CODE HERE --
simulate :: [[Cell]] -> ([(Hunter,Coordinate)],[(Prey,Coordinate)])

--simulate :: [[Cell]] -> ([(Hunter,(Int,Int))],[(Prey,(Int,Int))])
simulate cl =  free
            where
              plist = pfilter2d 0 cl --kordinatlarıyla birlikte prey listesi var
              hlist = hfilter2d 0 cl --kordşnatlatiyla birlikte hunter sitesi var
              sortplist = sortp plist
              sorthlist = sorth hlist
              allsteps =  allSTEPS  sorthlist sortplist cl
              free = freeit allsteps

--sorting yapmam gerekli


takefirst [] = []  --burda (prey/hunter,coordinate) yi sadece hunter/prey oliatesi olarak geri dönüyor
takefirst (x:xs) = (fst x):(takefirst xs)

findcoordinate x (p:ps)  --burda da verilern herhangi bir prey ve prey,coordinate den coordinate sini bulup döniyor
                |x == fst p = p
                |otherwise = findcoordinate x ps

sortwithcoordinate [] _ = []  --sortladıgımız preyleri coordinatelerine kavusturuyoruz
sortwithcoordinate  (x:xs) (p:ps) = (findcoordinate x (p:ps)):(sortwithcoordinate xs (p:ps))

reverseit [] = []
reverseit (p:ps) = (reverseit ps) ++ [p]           


sortp [] = []
sortp (p:ps) = lowsortcoordPrey
          where 
            preylist = takefirst (p:ps)
            sortpreylist = sort preylist --higest prioritiy
            lowsortcoordPrey = sortwithcoordinate sortpreylist (p:ps)
           -- reversedprey = reverseprey sortpreylist --prey listesi var lowest prioritiy seklinde



sorth [] = []
sorth (h:hs) = sortcoordHunter
          where
            hunterlist = takefirst (h:hs)
            sorthunterlist = sort hunterlist
            reversedHunter = reverseit sorthunterlist --hunter listesi var lowest prioritiy seklinde
            sortcoordHunter = sortwithcoordinate reversedHunter (h:hs)



--burda hunter yada pleyleri bir listede toplamak istedim ama bunların extra elemanlarından dolayo hata veridi ama X ve O ları kordinatlarıyla birlikte dogru veriyor.

isH :: Cell -> Bool
isH c = case c of O -> False
                  X -> False
                  T -> False
                  H (Hunter {})  -> True
                  P (Prey {}) -> False



hfilter _ _ [] = []
hfilter su sa (c:cs) 
            |x == True = (h,((sa,su),0)):(hfilter (su+1) sa cs)
            |otherwise = hfilter (su+1) sa cs
            where 
              x = isH (c)
              H h = c


hfilter2d _ [] = []
hfilter2d sa (c:cs) = (hfilter 0 sa c) ++ (hfilter2d (sa+1) cs)






isP :: Cell -> Bool
isP c = case c of O -> False
                  X -> False
                  T -> False
                  H (Hunter {})  -> False
                  P (Prey {}) -> True

pfilter _ _ [] = []
pfilter su sa (c:cs)
            |x == True = (p,((sa,su),0)):(pfilter (su+1) sa cs)
            |otherwise = pfilter (su+1) sa cs                   
            where 
              x = isP (c)
              P p = c

pfilter2d _ [] = [] --matrix halinde verien Cell tipinden prey tipine cevirir ve tum preyleri doner
pfilter2d sa (c:cs) = (pfilter 0 sa c) ++ (pfilter2d (sa+1) cs)










--adim atıldıtan sonra prey yenecek mi yenmeyecek mı yenirse (,((),bu)) bir olacak.

pcatch:: (Hunter,((Int,Int),Int)) -> [(Prey , ((Int  ,Int) , Int))] -> [(Prey , ((Int  ,Int) , Int))]
pcatch h [] = []
pcatch h (p:ps) | snd (snd h) == 2 = (p:ps)
        | snd (snd p) == 1 || fst (snd h) /= fst (snd p) = p:(pcatch h ps)
        | fst (snd h) == fst (snd p) = (pcatch h1 ps)
        where 
          hh = fst h
          pp = fst p
          energy |(hEnergy hh) > 100 = 100
            | otherwise = (hEnergy hh)
          h1 = ( (Hunter {hID = (hID hh) ,hlevel = (hlevel hh),hEnergy = energy,hNumberOfCatches = ((hNumberOfCatches hh) +1),hActions =(hActions hh)}) , (fst (snd h) , snd (snd h)+1) )
         -- p1 = (pp , ( fst (snd p) , 1 ) )

--hunter adim attıktan sonra kac tane prey yiyebiliyr ona bakar ve (,((),bu)) bir artar her yemede ev hunterin enerjisi 20 artar tabi.
addEnergy a 
          |(a+20) > 100 = 100
          |otherwise = a +20




hcatch:: (Hunter,((Int,Int),Int)) -> [(Prey , ((Int  ,Int) , Int))] -> (Hunter,((Int,Int),Int))
hcatch h [] = h
hcatch h (p:ps) | snd (snd h) == 2 = h
        | snd (snd p) == 1 || fst (snd h) /= fst (snd p) = (hcatch h ps)
        | fst (snd h) == fst (snd p) = (hcatch h1 ps)
        where 
          hh = fst h
          energy = addEnergy(hEnergy hh)
          h1 = ( (Hunter {hID = (hID hh) ,hlevel = (hlevel hh),hEnergy = energy,hNumberOfCatches = ((hNumberOfCatches hh) +1),hActions =(hActions hh)}) , (fst (snd h) , snd (snd h)+1) )
      



--sırasıyle hunterler hangilerini yiyebiliyor ona bakar ve isaretler

hscatch:: [(Hunter , ((Int  ,Int) , Int))] -> [(Prey , ((Int  ,Int) , Int))] -> [(Hunter , ((Int  ,Int) , Int))]
hscatch [] _ = []
hscatch h [] =  h
hscatch (h:hs) p = nh:(hscatch hs np)
    where 
      np = pcatch h p
      nh = hcatch h p
       

--sırasıyla hangi preyler yeniliyor onu kuntrol eder. 

pscatch:: [(Hunter , ((Int  ,Int) , Int))] -> [(Prey , ((Int  ,Int) , Int))] -> [(Prey , ((Int  ,Int) , Int))]
pscatch [] p = p
pscatch _ [] =  []
pscatch (h:hs) p = pscatch hs np
    where 
      np = pcatch h p
      nh = hcatch h p 



--burda bir sonraki adımın kordinatları var

findlast a w (x:xs) |w == N && saw == 0 = (saw,suw)
          |w == N && ((x:xs)!!(saw-1))!!(suw) == X = (saw,suw)
          |w == N = (saw-1,suw)

          |w == S && saw == (lensat-1) = (saw,suw)
          |w == S && ((x:xs)!!(saw+1))!!(suw) == X = (saw,suw)
          |w == S = (saw+1,suw)

          |w == W && suw == 0 = (saw,suw)
          |w == W && ((x:xs)!!(saw))!!(suw-1) == X = (saw,suw)
          |w == W = (saw,suw-1)

          |w == E && suw == (lensut-1) = (saw,suw)
          |w == E && ((x:xs)!!(saw))!!(suw+1) == X = (saw,suw)
          |w == E = (saw,suw+1)
          where 
            lensat = a!!0
            lensut =  a!!1
            saw = a!!2
            suw = a!!3





--prey'in adımı.


findlastpositionOfp pp npp acs (x:xs) 
							| ((x:xs)!!sat)!!sut == T = ((Prey { pID = (pID pp) , pEnergy = (pEnergy pp) -11 , pActions = acs }) ,(npp,0))
							|otherwise = ((Prey { pID = (pID pp) , pEnergy = (pEnergy pp) -1 , pActions = acs }) ,(npp,0))
							where
								sat = fst npp
								sut = snd npp

changeposionP p (x:xs) enrery
                          |enrery < 10 && ((x:xs)!!nsat)!!nsut == T =  ((Prey { pID = (pID pp) , pEnergy = 0 , pActions = acs }) ,((snd p)))
                          |enrery < 10 =  ((Prey { pID = (pID pp) , pEnergy =  enrery+1 , pActions = acs }) ,((snd p)))
                          |otherwise= lastpositionp
			where
				(ac:acs) = (pActions pp)				
				lsut = length x
				lsat = length (x:xs)
				initial = [lsat,lsut,fst (fst (snd p)),snd (fst (snd p))]
				npp = findlast initial ac (x:xs)
				nsat = fst (fst (snd p))
				nsut = snd (fst (snd p))
				pp = fst p
				lastpositionp = findlastpositionOfp pp npp acs (x:xs)



changeppreyposition p (x:xs) = changeposionP p (x:xs) enrery
						where
							pp = fst p
							enrery = (pEnergy pp)



changeAllPREYs [] _ = []
changeAllPREYs (p:ps) x = (changeppreyposition p x):(changeAllPREYs ps x)





--hunter adım atıyor dikkat!!!


changeposionH h (x:xs) = lastpositionh
			where
				(ac:acs) = (hActions hh)				
				lsut = length x
				lsat = length (x:xs)
				initial = [lsat,lsut,fst (fst (snd h)),snd (fst (snd h))]
				nhp = findlast initial ac (x:xs)
				nsat = fst nhp
				nsut = snd nhp
				hh = fst h
				lastpositionh = ((Hunter { hID = (hID hh) ,hlevel = (hlevel hh) , hEnergy = (hEnergy hh) - 1 ,hNumberOfCatches = (hNumberOfCatches hh), hActions = acs }) ,(nhp,0))
					--findlastpositionOfh hh nhp acs (x:xs)

changeHUNTERposition h (x:xs) 
						|enrery < 10 = ((Hunter { hID = (hID hh) ,hlevel = (hlevel hh) , hEnergy = (hEnergy hh) + 1 ,hNumberOfCatches = (hNumberOfCatches hh), hActions = hA }) ,(position,0))
						|otherwise = changeposionH h (x:xs)
						where
							hh = fst h
							(haction:hA) = (hActions hh)
							enrery = (hEnergy hh)
							position = fst (snd h)


changeAllHUNTERs  [] _ = [] --butun hunterlere adım bir sonraki adımını attırır yeme islemi yapılmaz burda ikinci elemanı bizim matriksimiz
changeAllHUNTERs (h:hs) p  = (changeHUNTERposition h p):(changeAllHUNTERs hs p)  













allSTEPS::[(Hunter,((Int,Int),Int))] -> [(Prey,((Int,Int),Int))] -> [[Cell]]-> ([(Hunter,((Int,Int),Int))],[(Prey,((Int,Int),Int))]) --burda satır sutunları ters veriyor ve son eeman fazla
allSTEPS (h:hs) [] _ = ((h:hs),[])
allSTEPS (h:hs) (p:ps) mx
                      |(numCATCH == 0)  = ((h:hs),(p:ps))   
                      |otherwise = allSTEPS sortedH sortedP mx
                        where
                          hh = fst h
                          numCATCH = (length (hActions hh))
                          changedHUNTER = changeAllHUNTERs (h:hs) mx
                          changedPREY = changeAllPREYs (p:ps) mx
                          preyAfterCATCH= pscatch changedHUNTER changedPREY
                          hunterAfterCATCH = hscatch changedHUNTER changedPREY
                          sortedH = sorth hunterAfterCATCH
                          sortedP = sortp preyAfterCATCH



helpTOfree [] = []
helpTOfree (x:xs) = curTuple:(helpTOfree xs)
            where
              sat = fst (fst (snd x))
              sut = snd (fst (snd x))
              curElem = fst x
              curTuple = (curElem,(sut,sat))



freeit allsteps = ((helpTOfree hunter),(helpTOfree prey))
        where
        hunter = fst allsteps
        prey = snd allsteps                          



                          
