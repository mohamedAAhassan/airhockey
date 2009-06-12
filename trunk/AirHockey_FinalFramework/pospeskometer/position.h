#ifndef __POSITION_H
#define __POSITION_H

class Position //razred position za koordinate
{
public:
	double x,y,z;
	double Cas,HitrostX,HitrostY,HitrostZ,PremikX,PremikY,PremikZ,frekvenca;

	Position(int x1,int y1,int z1) 
	{ 
		x=x1;
		y=y1;
		z=z1; 
	}

	Position() 
	{
		x = y = z = Cas = HitrostX = HitrostY = HitrostZ = PremikX = PremikY = PremikZ = 0;
	}
	Position(Position prev, double x1,double y1,double z1,double cas1) 
	{
		x=prev.x-x1;y=prev.y-y1;z=prev.z-z1;Cas=cas1;HitrostX=x*(Cas-prev.Cas);HitrostY=y*(Cas-prev.Cas);HitrostZ=z*(Cas-prev.Cas);
	}
	void setPos(Position prev, double x1,double y1,double z1,double cas1) 
	{
		x=x1;y=y1;z=z1;Cas=cas1;;
	}
	void setPos() 
	{
		x=y=z=Cas=HitrostX=HitrostY=HitrostZ=0;
		PremikX=0;
		PremikY=PremikZ=-1;
	}

	void checkPos(Position prev)
	{
		HitrostX=x*(Cas-prev.Cas);
		HitrostY=y*(Cas-prev.Cas);
		HitrostZ=z*(Cas-prev.Cas);
		PremikX=prev.PremikX+(HitrostX*(Cas-prev.Cas))/4;
		PremikY=prev.PremikY+(HitrostY*(Cas-prev.Cas))/2;
		PremikZ=prev.PremikZ+(HitrostZ*(Cas-prev.Cas))/4;
		frekvenca=1/(Cas-prev.Cas);
		if(PremikX<-1.1)PremikX=-1.1;
		if(PremikX>1.1)PremikX=1.1;
		if(PremikY<-2.9)PremikY=-2.9;
		if(PremikY>0)PremikY=0;
//		if(PremikZ<0)PremikZ=0;
//		if(PremikZ>500)PremikZ=500;
	}

	bool checkPos_meje()
	{
		if(x<10)return false;
		if(x>490)return false;
		if(y<10)return false;
		if(y>490)return false;

		return true;
	}
};

#endif