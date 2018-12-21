#include "Picture.cpp"

int main()
{
	Picture beach, baloons, bigTree, circles, coins,
	film, flygga, monaLisa, monkey, neurons, neurons2,
	neurons3, neurons4, phone, tree, vegetables;
	beach.get("beach.pgm"); baloons.get("baloons.pgm");
	bigTree.get("bigTree.pgm"); circles.get("circles.pgm");
	coins.get("coins.pgm"); film.get("film.pgm");
	flygga.get("flygga.pgm"); monaLisa.get("monaLisa.pgm");
	monkey.get("monkey.pgm"); neurons.get("neurons.pgm");
	neurons2.get("neurons2.pgm"); neurons3.get("neurons3.pgm");
	neurons4.get("neurons4.pgm"); phone.get("phone.pgm");
	tree.get("tree.pgm"); vegetables.get("vegetables.pgm");
	flygga >>= 2;
	(flygga * flygga) ->*("multi.pgm");
	(beach + baloons) ->*("add.pgm");
	(monkey - tree) ->*("sub.pgm");
	
	(vegetables * 2) ->*("multiConst.pgm");
	(phone + 64) ->*("addConst.pgm");
	(coins - 120) ->*("subConst.pgm");
	(monaLisa / 2) ->*("divConst.pgm");
	(coins % 31) ->*("modConst.pgm");
	
	(~circles) ->*("neg.pgm");
	
	Picture rotateCVV = -vegetables;
	(rotateCVV) ->*("rotateCVV.pgm");
	+vegetables;
	Picture rotateCV = +vegetables;
	(rotateCV) ->*("rotateCV.pgm");
	
	(monaLisa, film) ->*("panorama.pgm");
	for (int i = 0; i < (beach.getHeight() - circles.getHeight()) >> 1; ++i)
	{
		--circles;
		circles--;
	}
	Picture panorama2 = (beach, circles);
	panorama2 ->*("panorama2.pgm");
	
	for (int i = 0; i < panorama2.getHeight() - phone.getHeight(); ++i)
	{
		phone--;
	}
	(panorama2, phone) ->*("panorama3.pgm");
}
