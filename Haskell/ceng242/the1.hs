data Cell = H | P | O | X deriving (Read,Show,Eq)
data Result = Fail | Caught (Int,Int) deriving (Read,Show,Eq)
data Direction = N | S | E | W deriving (Read,Show,Eq)

simulate :: [[Cell]] -> [(Direction, Direction)] -> Result
-- DO NOT CHANGE ABOVE THIS LINE, WRITE YOUR CODE BELOW --





finda a p [] = -1
finda a p (x:xs)
	|a == x = p
	|otherwise = finda a (p+1) xs




change w p [] = []
change w p (x:xs)
	|p == 0 = w:xs
	|otherwise = x:(change w (p-1) xs)




find2d a p [] = (-1,-1)
find2d a p (x:xs) |b /= -1 = (p,b)
				  |otherwise = find2d a (p+1) xs
					where b = finda a 0 x




changeh w f s [] = []
changeh w f s (x:xs) |f == 0  = (change w s x):xs
				   |otherwise = x:(changeh w (f-1) s xs)

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



					
simulate as [] = Fail
simulate (a:as) (b:bs)|lastH == lastP = Caught (snd lastP,fst lastP)
					  |lastH == findH && lastP == findP = simulate (a:as) bs
					  |lastH == findH = simulate (changeh O (fst findP) (snd findP) (changeh P (fst lastP) (snd lastP) (a:as) )) bs
					  |lastP == findP = simulate (changeh O (fst findH) (snd findH) (changeh H (fst lastH) (snd lastH) (a:as) )) bs
					  |(lastH == findP) && (lastP == findH) = simulate (changeh P (fst lastP) (snd lastP) (changeh H (fst lastH) (snd lastH) (a:as))) bs
					  |lastH == findP = simulate (changeh O (fst findH) (snd findH) (changeh P (fst lastP) (snd lastP) (changeh H (fst lastH) (snd lastH) (a:as) ) )) bs
					  |lastP == findH = simulate (changeh O (fst findP) (snd findP) (changeh P (fst lastP) (snd lastP) (changeh H (fst lastH) (snd lastH) (a:as) ) ) ) bs
					  |otherwise = simulate (changeh O (fst findP) (snd findP) (changeh O (fst findH) (snd findH) (changeh P (fst lastP) (snd lastP) (changeh H (fst lastH) (snd lastH) (a:as) ) )))	bs
				where
					lsut = length a
					lsat = length (a:as) 						
					findH = find2d H 0 (a:as)
					findP = find2d P 0 (a:as)
					lastH = findlast [lsat,lsut,fst findH,snd findH] (fst b) (a:as)
					lastP = findlast [lsat,lsut,fst findP,snd findP] (snd b) (a:as) 

					
