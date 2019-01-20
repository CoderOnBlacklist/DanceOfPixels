#ifndef PSEUDO_PHYSICS_H
#define PSEUDO_PHYSICS_H

typedef struct
{
	float max_x,min_x,max_y,min_y;
	
	float rotational_speed_limit;
	float angle,angular_vel;
	
	vector2f pos,vel;
	float dir,sp;
	vector_array2f *point;
	float margin;
}irregular;

irregular irregularC(vector2f pos,vector_array2f *point,float margin)
{
	irregular obj;
	
	obj.angle=0;
	obj.angular_vel=0;
	
	obj.pos=pos;
	obj.vel=vec2f(0,0);
	
	obj.sp=0;
	obj.dir=0;
	
	obj.point=point;
	obj.margin=margin;

	{
		float d,largest_d=0;
		int i;
		for(i=0; i<point->n; i++)
		{
			d=lengthv2f(point->v[i]);
			if(d>largest_d)
			{
				largest_d=d;
			}
		}
		
		obj.rotational_speed_limit=1/largest_d;
		
		obj.max_x=-10000;
		obj.max_y=-10000;
		obj.min_x= 10000;
		obj.min_y= 10000;
		for(i=0; i<point->n; i++)
		{
			if(point->v[i].e[0]>obj.max_x) obj.max_x=point->v[i].e[0];
			if(point->v[i].e[1]>obj.max_y) obj.max_y=point->v[i].e[1];
			if(point->v[i].e[0]<obj.min_x) obj.min_x=point->v[i].e[0];
			if(point->v[i].e[1]<obj.min_y) obj.min_y=point->v[i].e[1];
		}
		
		obj.max_x+=obj.margin+1;
		obj.max_y+=obj.margin+1;
		obj.min_x-=obj.margin+1;
		obj.min_y-=obj.margin+1;
	}
	
	return obj;
}

void irregularSetPosition(irregular *obj,vector2f pos)
{
	obj->pos=pos;
}
void irregularSetVelocity(irregular *obj,vector2f vel)
{
	obj->vel=vel;
	obj->dir=getAnglev2f(vel);
	obj->sp=lengthv2f(vel);
}
void irregularSetSpeed(irregular *obj,float sp)
{
	if(lengthv2f(obj->vel))
	{
		obj->vel=scalev2f(obj->vel,sp/lengthv2f(obj->vel));
		obj->sp=sp;
	}
	else
	{
		obj->vel=vec2f(cos(obj->dir)*sp,sin(obj->dir)*sp);
		obj->sp=sp;
	}
}
void irregularIncSpeed(irregular *obj,float x)
{
	obj->vel=scalev2f(obj->vel,(obj->sp+x)/(obj->sp));
	obj->sp+=x;
	if(obj->sp<0)
	{
		obj->vel=vec2f(0,0);
		obj->sp=0;
	}
}
/*
void irregularRotationalFriction(irregular *obj,float x)
{
	if(obj->angular_vel>x)
		obj->angular_vel-=x;
	else if(obj->angular_vel<-x)
		obj->angular_vel+=x;
	else
		obj->angular_vel=0;
}*/

void irregularHorizontalSpeedLimit(irregular *obj,float x)
{
		 if(obj->vel.e[0]> x)
		obj->vel.e[0]=+x;
	else if(obj->vel.e[0]<-x)
		obj->vel.e[0]=-x;
}

void irregularVerticalSpeedLimit(irregular *obj,float x)
{
		 if(obj->vel.e[1]> x)
		obj->vel.e[1]=+x;
	else if(obj->vel.e[1]<-x)
		obj->vel.e[1]=-x;
}

void irregularHorizontalFriction(irregular *obj,float x)
{
		 if(obj->vel.e[0]> x)
		obj->vel.e[0]-=x;
	else if(obj->vel.e[0]<-x)
		obj->vel.e[0]+=x;
	else
		obj->vel.e[0]=0;
}

void irregularVerticalFriction(irregular *obj,float x)
{
		 if(obj->vel.e[1]> x)
		obj->vel.e[1]-=x;
	else if(obj->vel.e[1]<-x)
		obj->vel.e[1]+=x;
	else
		obj->vel.e[1]=0;
}

void irregularRotationalFriction(irregular *obj,float x)
{
	if(obj->angular_vel>x)
		obj->angular_vel-=x;
	else if(obj->angular_vel<-x)
		obj->angular_vel+=x;
	else
		obj->angular_vel=0;
}

void irregularSetDirection(irregular *obj,float dir)
{
	obj->vel.e[0]=cos(dir)*obj->sp;
	obj->vel.e[1]=sin(dir)*obj->sp;
	obj->dir=dir;
}

void irregularApplyImpulse(irregular *obj,vector2f size,float s)
{
	obj->vel.e[0]+=size.e[0]*s;
	obj->vel.e[1]+=size.e[1]*s;
	
	obj->dir=getAnglev2f(obj->vel);
	obj->sp=lengthv2f(obj->vel);
}

void irregularApplyImpulseRotational(irregular *obj,vector2f size,float s,vector2f pos,float s2)
{
	float moment;
	vector2f d;
	d=subv2f(pos,obj->pos);
	moment=-crossf(vec2f_to_vec3f(size),vec2f_to_vec3f(d)).e[2];
	
	obj->angular_vel+=moment*s2;
	
	obj->vel.e[0]+=size.e[0]*s;
	obj->vel.e[1]+=size.e[1]*s;
	
	obj->dir=getAnglev2f(obj->vel);
	obj->sp=lengthv2f(obj->vel);
}
void irregularApplyImpulseRotationalRelative(irregular *obj,vector2f size,float s,vector2f pos,float s2)
{
	float moment;
	moment=-crossf(vec2f_to_vec3f(size),vec2f_to_vec3f(pos)).e[2];
	
	obj->angular_vel+=moment*s2;
	
	obj->vel.e[0]+=size.e[0]*s;
	obj->vel.e[1]+=size.e[1]*s;
	
	obj->dir=getAnglev2f(obj->vel);
	obj->sp=lengthv2f(obj->vel);
}

int irregularCollision(irregular *obj1,irregular *obj2)
{
	int i,j;
	vector2f p,p1,p2;
	arrow2f arr;
	vector2f self1,self2,self3,self4,other1,other2,other3,other4;
	
	self1=vec2f(obj1->min_x,obj1->min_y);
	self2=vec2f(obj1->max_x,obj1->min_y);
	self3=vec2f(obj1->max_x,obj1->max_y);
	self4=vec2f(obj1->min_x,obj1->max_y);
	
	self1=rotatev2f(self1,obj1->angle);
	self2=rotatev2f(self2,obj1->angle);
	self3=rotatev2f(self3,obj1->angle);
	self4=rotatev2f(self4,obj1->angle);
	
	self1=addv2f(self1,obj1->pos);
	self2=addv2f(self2,obj1->pos);
	self3=addv2f(self3,obj1->pos);
	self4=addv2f(self4,obj1->pos);
	
	other1=vec2f(obj2->min_x,obj2->min_y);
	other2=vec2f(obj2->max_x,obj2->min_y);
	other3=vec2f(obj2->max_x,obj2->max_y);
	other4=vec2f(obj2->min_x,obj2->max_y);
	
	other1=rotatev2f(other1,obj2->angle);
	other2=rotatev2f(other2,obj2->angle);
	other3=rotatev2f(other3,obj2->angle);
	other4=rotatev2f(other4,obj2->angle);
	
	other1=addv2f(other1,obj2->pos);
	other2=addv2f(other2,obj2->pos);
	other3=addv2f(other3,obj2->pos);
	other4=addv2f(other4,obj2->pos);
	
	if(
		!TriangleToTriangle
		(
		tri2fv(self1,self2,self3),
		tri2fv(other1,other2,other3)
		)
		&&
		!TriangleToTriangle
		(
		tri2fv(self3,self4,self1),
		tri2fv(other1,other2,other3)
		)
		&&
		!TriangleToTriangle
		(
		tri2fv(self1,self2,self3),
		tri2fv(other3,other4,other1)
		)
		&&
		!TriangleToTriangle
		(
		tri2fv(self3,self4,self1),
		tri2fv(other3,other4,other1)
		)
	  )
	return 0;
	
	for(i=0; i<obj1->point->n-1; i++)
		for(j=0; j<obj2->point->n; j++)
		{
			p1=obj1->point->v[i];
			p2=obj1->point->v[i+1];
			p1=rotatev2f(p1,obj1->angle);
			p2=rotatev2f(p2,obj1->angle);
			p1=addv2f(p1,obj1->pos);
			p2=addv2f(p2,obj1->pos);
			
			p=obj2->point->v[j];
			p=rotatev2f(p,obj2->angle);
			p=addv2f(p,obj2->pos);
			
			arr=arr2fv(p1,p2);
			if(CircleToThickLineSegment(p,obj2->margin/2,arr,obj1->margin/2)) return 1;
		}
	
	for(i=0; i<obj1->point->n; i++)
		for(j=0; j<obj2->point->n-1; j++)
		{
			p1=obj2->point->v[j];
			p2=obj2->point->v[j+1];
			p1=rotatev2f(p1,obj2->angle);
			p2=rotatev2f(p2,obj2->angle);
			p1=addv2f(p1,obj2->pos);
			p2=addv2f(p2,obj2->pos);
			
			p=obj1->point->v[i];
			p=rotatev2f(p,obj1->angle);
			p=addv2f(p,obj1->pos);
			
			arr=arr2fv(p1,p2);
			if(CircleToThickLineSegment(p,obj1->margin/2,arr,obj2->margin/2)) return 1;
		}
	
	return 0;
}

int irregularLineOther(irregular *obj1,irregular *obj2)
{
	int i,j;
	vector2f p,p1,p2;
	arrow2f arr;
	
	for(i=0; i<obj1->point->n; i++)
		for(j=0; j<obj2->point->n-1; j++)
		{
			p1=obj2->point->v[j];
			p2=obj2->point->v[j+1];
			p1=rotatev2f(p1,obj2->angle);
			p2=rotatev2f(p2,obj2->angle);
			p1=addv2f(p1,obj2->pos);
			p2=addv2f(p2,obj2->pos);
			
			p=obj1->point->v[i];
			p=rotatev2f(p,obj1->angle);
			p=addv2f(p,obj1->pos);
			
			arr=arr2fv(p1,p2);
			if(CircleToThickLineSegment(p,obj1->margin/2,arr,obj2->margin/2)) return j;
		}
	
	return -1;

}

int irregularPointSelf(irregular *obj1,irregular *obj2)
{
	int i,j;
	vector2f p,p1,p2;
	arrow2f arr;
	
	for(i=0; i<obj1->point->n; i++)
		for(j=0; j<obj2->point->n-1; j++)
		{
			p1=obj2->point->v[j];
			p2=obj2->point->v[j+1];
			p1=rotatev2f(p1,obj2->angle);
			p2=rotatev2f(p2,obj2->angle);
			p1=addv2f(p1,obj2->pos);
			p2=addv2f(p2,obj2->pos);
			
			p=obj1->point->v[i];
			p=rotatev2f(p,obj1->angle);
			p=addv2f(p,obj1->pos);
			
			arr=arr2fv(p1,p2);
			if(CircleToThickLineSegment(p,obj1->margin/2,arr,obj2->margin/2)) return i;
		}
	
	return -1;

}

int irregularLineSelf(irregular *obj1,irregular *obj2)
{
	int i,j;
	vector2f p,p1,p2;
	arrow2f arr;
	
	for(i=0; i<obj1->point->n-1; i++)
		for(j=0; j<obj2->point->n; j++)
		{
			p1=obj1->point->v[i];
			p2=obj1->point->v[i+1];
			p1=rotatev2f(p1,obj1->angle);
			p2=rotatev2f(p2,obj1->angle);
			p1=addv2f(p1,obj1->pos);
			p2=addv2f(p2,obj1->pos);
			
			p=obj2->point->v[j];
			p=rotatev2f(p,obj2->angle);
			p=addv2f(p,obj2->pos);
			
			arr=arr2fv(p1,p2);
			if(CircleToThickLineSegment(p,obj2->margin/2,arr,obj1->margin/2)) return i;
		}
	
	return -1;
}

int irregularPointOther(irregular *obj1,irregular *obj2)
{
	int i,j;
	vector2f p,p1,p2;
	arrow2f arr;
	
	for(i=0; i<obj1->point->n-1; i++)
		for(j=0; j<obj2->point->n; j++)
		{
			p1=obj1->point->v[i];
			p2=obj1->point->v[i+1];
			p1=rotatev2f(p1,obj1->angle);
			p2=rotatev2f(p2,obj1->angle);
			p1=addv2f(p1,obj1->pos);
			p2=addv2f(p2,obj1->pos);
			
			p=obj2->point->v[j];
			p=rotatev2f(p,obj2->angle);
			p=addv2f(p,obj2->pos);
			
			arr=arr2fv(p1,p2);
			if(CircleToThickLineSegment(p,obj2->margin/2,arr,obj1->margin/2)) return j;
		}
	
	return -1;
}

void irregularResolutionBoth(irregular *obj1,irregular *obj2,float bounce,float force)
{
	float perpendicular_size;
	vector2f relative_vel,perpendicular_vel;
	vector2f v1,v2;
	vector2f normal1,normal2;
	int i_self,i_other,i_point;
	vector2f point;
	i_self=irregularLineSelf(obj1,obj2);
	i_other=irregularLineOther(obj1,obj2);
	
	relative_vel=subv2f(obj1->vel,obj2->vel);

	if(i_self!=-1)
	{
		i_point=irregularPointOther(obj1,obj2);
		point=obj2->point->v[i_point];
		point=rotatev2f(point,obj2->angle);
		point=addv2f(point,obj2->pos);
		
		v2=subv2f(obj1->point->v[i_self+1],obj1->point->v[i_self]);
		v2=rotatev2f(v2,obj1->angle);
		normal2=normalizev2f(vec3f_to_vec2f(crossf(vec3f(0,0,1),vec2f_to_vec3f(v2))));
		
		while(i_self!=-1)
		{
			obj1->pos=addv2f(obj1->pos,scalev2f(normal2, 0.5));
			obj2->pos=addv2f(obj2->pos,scalev2f(normal2,-0.5));
			i_self=irregularLineSelf(obj1,obj2);
		}
		obj1->pos=addv2f(obj1->pos,scalev2f(normal2,-0.5));
		obj2->pos=addv2f(obj2->pos,scalev2f(normal2, 0.5));
		i_self=0;
		while(i_self!=-1)
		{
			obj1->pos=addv2f(obj1->pos,scalev2f(normal2, 0.05));
			obj2->pos=addv2f(obj2->pos,scalev2f(normal2,-0.05));
			i_self=irregularLineSelf(obj1,obj2);
		}
		
		perpendicular_size=dotv2f(scalev2f(relative_vel,-1),normal2)*(bounce+1);
		perpendicular_vel=scalev2f(normal2,perpendicular_size);

		irregularApplyImpulse(obj1,normal2,force*perpendicular_size);
		irregularApplyImpulse(obj2,scalev2f(normal2,-1),force*perpendicular_size);
		
	}
	else if(i_other!=-1)
	{
		i_point=irregularPointSelf(obj1,obj2);
		point=obj1->point->v[i_point];
		point=rotatev2f(point,obj1->angle);
		point=addv2f(point,obj1->pos);
		
		v1=subv2f(obj2->point->v[i_other+1],obj2->point->v[i_other]);
		v1=rotatev2f(v1,obj2->angle);
		normal1=normalizev2f(vec3f_to_vec2f(crossf(vec2f_to_vec3f(v1),vec3f(0,0,1))));
		
		while(i_other!=-1)
		{
			obj1->pos=addv2f(obj1->pos,scalev2f(normal1, 0.5));
			obj2->pos=addv2f(obj2->pos,scalev2f(normal1,-0.5));
			i_other=irregularLineOther(obj1,obj2);
		}
		obj1->pos=addv2f(obj1->pos,scalev2f(normal1,-0.5));
		obj2->pos=addv2f(obj2->pos,scalev2f(normal1, 0.5));
		i_other=0;
		while(i_other!=-1)
		{
			obj1->pos=addv2f(obj1->pos,scalev2f(normal1, 0.05));
			obj2->pos=addv2f(obj2->pos,scalev2f(normal1,-0.05));
			i_other=irregularLineOther(obj1,obj2);
		}
		
		perpendicular_size=dotv2f(scalev2f(relative_vel,-1),normal1)*(bounce+1);
		perpendicular_vel=scalev2f(normal1,perpendicular_size);
		
		irregularApplyImpulse(obj1,normal1,force*perpendicular_size);
		irregularApplyImpulse(obj2,scalev2f(normal1,-1),force*perpendicular_size);
	}
}


void irregularResolutionRotationalBoth(irregular *obj1,irregular *obj2,float bounce,float force,float angular_effect)
{
	float perpendicular_size;
	vector2f relative_vel,perpendicular_vel;
	vector2f v1,v2;
	vector2f normal1,normal2;
	int i_self,i_other,i_point;
	vector2f point;
	i_self=irregularLineSelf(obj1,obj2);
	i_other=irregularLineOther(obj1,obj2);
	
	relative_vel=subv2f(obj1->vel,obj2->vel);

	if(i_self!=-1)
	{
		i_point=irregularPointOther(obj1,obj2);
		point=obj2->point->v[i_point];
		point=rotatev2f(point,obj2->angle);
		point=addv2f(point,obj2->pos);
		
		v2=subv2f(obj1->point->v[i_self+1],obj1->point->v[i_self]);
		v2=rotatev2f(v2,obj1->angle);
		normal2=normalizev2f(vec3f_to_vec2f(crossf(vec3f(0,0,1),vec2f_to_vec3f(v2))));
		
		while(i_self!=-1)
		{
			obj1->pos=addv2f(obj1->pos,scalev2f(normal2, 0.5));
			obj2->pos=addv2f(obj2->pos,scalev2f(normal2,-0.5));
			i_self=irregularLineSelf(obj1,obj2);
		}
		obj1->pos=addv2f(obj1->pos,scalev2f(normal2,-0.5));
		obj2->pos=addv2f(obj2->pos,scalev2f(normal2, 0.5));
		i_self=0;
		while(i_self!=-1)
		{
			obj1->pos=addv2f(obj1->pos,scalev2f(normal2, 0.05));
			obj2->pos=addv2f(obj2->pos,scalev2f(normal2,-0.05));
			i_self=irregularLineSelf(obj1,obj2);
		}
		
		perpendicular_size=dotv2f(scalev2f(relative_vel,-1),normal2)*(bounce+1);
		perpendicular_vel=scalev2f(normal2,perpendicular_size);

		irregularApplyImpulseRotational(obj1,normal2,force*perpendicular_size,point,angular_effect);
		irregularApplyImpulseRotational(obj2,scalev2f(normal2,-1),force*perpendicular_size,point,angular_effect);
		
	}
	else if(i_other!=-1)
	{
		i_point=irregularPointSelf(obj1,obj2);
		point=obj1->point->v[i_point];
		point=rotatev2f(point,obj1->angle);
		point=addv2f(point,obj1->pos);
		
		v1=subv2f(obj2->point->v[i_other+1],obj2->point->v[i_other]);
		v1=rotatev2f(v1,obj2->angle);
		normal1=normalizev2f(vec3f_to_vec2f(crossf(vec2f_to_vec3f(v1),vec3f(0,0,1))));
		
		while(i_other!=-1)
		{
			obj1->pos=addv2f(obj1->pos,scalev2f(normal1, 0.5));
			obj2->pos=addv2f(obj2->pos,scalev2f(normal1,-0.5));
			i_other=irregularLineOther(obj1,obj2);
		}
		obj1->pos=addv2f(obj1->pos,scalev2f(normal1,-0.5));
		obj2->pos=addv2f(obj2->pos,scalev2f(normal1, 0.5));
		i_other=0;
		while(i_other!=-1)
		{
			obj1->pos=addv2f(obj1->pos,scalev2f(normal1, 0.05));
			obj2->pos=addv2f(obj2->pos,scalev2f(normal1,-0.05));
			i_other=irregularLineOther(obj1,obj2);
		}
		
		perpendicular_size=dotv2f(scalev2f(relative_vel,-1),normal1)*(bounce+1);
		perpendicular_vel=scalev2f(normal1,perpendicular_size);
		
		irregularApplyImpulseRotational(obj1,normal1,force*perpendicular_size,point,angular_effect);
		irregularApplyImpulseRotational(obj2,scalev2f(normal1,-1),force*perpendicular_size,point,angular_effect);
	}
}

void irregularResolutionRotational(irregular *obj1,irregular *obj2,float positional_impulse,float bounce,float force,float angular_effect)
{
	float perpendicular_size;
	vector2f relative_vel,perpendicular_vel;
	vector2f v1,v2;
	vector2f normal1,normal2;
	int i_self,i_other,i_point;
	vector2f point;
	i_self=irregularLineSelf(obj1,obj2);
	i_other=irregularLineOther(obj1,obj2);
	
	relative_vel=subv2f(obj1->vel,obj2->vel);
	
	
	if(i_self!=-1)
	{
		i_point=irregularPointOther(obj1,obj2);
		point=obj2->point->v[i_point];
		point=rotatev2f(point,obj2->angle);
		point=addv2f(point,obj2->pos);
		
		v2=subv2f(obj1->point->v[i_self+1],obj1->point->v[i_self]);
		v2=rotatev2f(v2,obj1->angle);
		normal2=normalizev2f(vec3f_to_vec2f(crossf(vec3f(0,0,1),vec2f_to_vec3f(v2))));
		
		obj1->pos=addv2f(obj1->pos,scalev2f(normal2,positional_impulse));
		
		perpendicular_size=dotv2f(scalev2f(relative_vel,-1),normal2)*(bounce+1);
		perpendicular_vel=scalev2f(normal2,perpendicular_size);

		irregularApplyImpulseRotational(obj1,normal2,force*perpendicular_size,point,angular_effect);
		
	}
	else if(i_other!=-1)
	{
		i_point=irregularPointSelf(obj1,obj2);
		point=obj1->point->v[i_point];
		point=rotatev2f(point,obj1->angle);
		point=addv2f(point,obj1->pos);
		
		v1=subv2f(obj2->point->v[i_other+1],obj2->point->v[i_other]);
		v1=rotatev2f(v1,obj2->angle);
		normal1=normalizev2f(vec3f_to_vec2f(crossf(vec2f_to_vec3f(v1),vec3f(0,0,1))));
		
		obj1->pos=addv2f(obj1->pos,scalev2f(normal1,positional_impulse));
		
		perpendicular_size=dotv2f(scalev2f(relative_vel,-1),normal1)*(bounce+1);
		perpendicular_vel=scalev2f(normal1,perpendicular_size);
		
		irregularApplyImpulseRotational(obj1,normal1,force*perpendicular_size,point,angular_effect);
	}
}

void irregularResolutionRotationalFriction(irregular *obj1,irregular *obj2,float positional_impulse,float bounce,float force,float angular_effect,float x)
{
	vector2f friction;
	float perpendicular_size;
	vector2f relative_vel,perpendicular_vel;
	vector2f v1,v2;
	vector2f normal1,normal2;
	int i_self,i_other,i_point;
	vector2f point;
	i_self=irregularLineSelf(obj1,obj2);
	i_other=irregularLineOther(obj1,obj2);
	
	relative_vel=subv2f(obj1->vel,obj2->vel);
	
	
	if(i_self!=-1)
	{
		i_point=irregularPointOther(obj1,obj2);
		point=obj2->point->v[i_point];
		point=rotatev2f(point,obj2->angle);
		point=addv2f(point,obj2->pos);
		
		v2=subv2f(obj1->point->v[i_self+1],obj1->point->v[i_self]);
		v2=rotatev2f(v2,obj1->angle);
		normal2=normalizev2f(vec3f_to_vec2f(crossf(vec3f(0,0,1),vec2f_to_vec3f(v2))));
			
		obj1->pos=addv2f(obj1->pos,scalev2f(normal2,positional_impulse));

		perpendicular_size=dotv2f(scalev2f(relative_vel,-1),normal2)*(bounce+1);
		perpendicular_vel=scalev2f(normal2,perpendicular_size);

		friction=addv2f(obj1->vel,perpendicular_vel);
		
		if(lengthv2f(friction)>x)
		{
			friction=normalizev2f(friction);
			friction=scalev2f(friction,-x);
		
			obj1->vel=addv2f(obj1->vel,friction);
		}
		else
		{
			friction=scalev2f(friction,-1);
		
			obj1->vel=addv2f(obj1->vel,friction);
		}

		irregularApplyImpulseRotational(obj1,normal2,force*perpendicular_size,point,angular_effect);
		
		
	}
	else if(i_other!=-1)
	{
		i_point=irregularPointSelf(obj1,obj2);
		point=obj1->point->v[i_point];
		point=rotatev2f(point,obj1->angle);
		point=addv2f(point,obj1->pos);
		
		v1=subv2f(obj2->point->v[i_other+1],obj2->point->v[i_other]);
		v1=rotatev2f(v1,obj2->angle);
		normal1=normalizev2f(vec3f_to_vec2f(crossf(vec2f_to_vec3f(v1),vec3f(0,0,1))));
		
		obj1->pos=addv2f(obj1->pos,scalev2f(normal1,positional_impulse));
		
		perpendicular_size=dotv2f(scalev2f(relative_vel,-1),normal1)*(bounce+1);
		perpendicular_vel=scalev2f(normal1,perpendicular_size);
		
		friction=addv2f(obj1->vel,perpendicular_vel);
		
		if(lengthv2f(friction)>x)
		{
			friction=normalizev2f(friction);
			friction=scalev2f(friction,-x);
		
			obj1->vel=addv2f(obj1->vel,friction);
		}
		else
		{
			friction=scalev2f(friction,-1);
		
			obj1->vel=addv2f(obj1->vel,friction);
		}
		
		irregularApplyImpulseRotational(obj1,normal1,force*perpendicular_size,point,angular_effect);
		
	}
}

void irregularResolution(irregular *obj1,irregular *obj2,float positional_impulse,float bounce,float force)
{
	float perpendicular_size;
	vector2f relative_vel,perpendicular_vel;
	vector2f v1,v2;
	vector2f normal1,normal2;
	int i_self,i_other,i_point;
	vector2f point;
	i_self=irregularLineSelf(obj1,obj2);
	i_other=irregularLineOther(obj1,obj2);
	
	relative_vel=subv2f(obj1->vel,obj2->vel);
	
	if(i_self!=-1 && i_other!=-1)
	return;
	if(i_other!=-1)
	{
		i_point=irregularPointSelf(obj1,obj2);
		point=obj1->point->v[i_point];
		point=rotatev2f(point,obj1->angle);
		point=addv2f(point,obj1->pos);
		
		v1=subv2f(obj2->point->v[i_other+1],obj2->point->v[i_other]);
		v1=rotatev2f(v1,obj2->angle);
		normal1=normalizev2f(vec3f_to_vec2f(crossf(vec2f_to_vec3f(v1),vec3f(0,0,1))));
		
		obj1->pos=addv2f(obj1->pos,scalev2f(normal1,positional_impulse));
		
		perpendicular_size=dotv2f(scalev2f(relative_vel,-1),normal1)*(bounce+1);
		perpendicular_vel=scalev2f(normal1,perpendicular_size);
		
		irregularApplyImpulse(obj1,normal1,force*perpendicular_size);
	}
	else if(i_self!=-1)
	{
		i_point=irregularPointOther(obj1,obj2);
		point=obj2->point->v[i_point];
		point=rotatev2f(point,obj2->angle);
		point=addv2f(point,obj2->pos);
		
		v2=subv2f(obj1->point->v[i_self+1],obj1->point->v[i_self]);
		v2=rotatev2f(v2,obj1->angle);
		normal2=normalizev2f(vec3f_to_vec2f(crossf(vec3f(0,0,1),vec2f_to_vec3f(v2))));
		
		obj1->pos=addv2f(obj1->pos,scalev2f(normal2,positional_impulse));
			
		perpendicular_size=dotv2f(scalev2f(relative_vel,-1),normal2)*(bounce+1);
		perpendicular_vel=scalev2f(normal2,perpendicular_size);

		irregularApplyImpulse(obj1,normal2,force*perpendicular_size);
		
	}
}

void irregularResolutionFriction(irregular *obj1,irregular *obj2,float positional_impulse,float bounce,float force,float x)
{
	vector2f friction;
	float perpendicular_size;
	vector2f relative_vel,perpendicular_vel;
	vector2f v1,v2;
	vector2f normal1,normal2;
	int i_self,i_other,i_point;
	vector2f point;
	i_self=irregularLineSelf(obj1,obj2);
	i_other=irregularLineOther(obj1,obj2);
	
	relative_vel=subv2f(obj1->vel,obj2->vel);
	
	
	if(i_self!=-1)
	{
		i_point=irregularPointOther(obj1,obj2);
		point=obj2->point->v[i_point];
		point=rotatev2f(point,obj2->angle);
		point=addv2f(point,obj2->pos);
		
		v2=subv2f(obj1->point->v[i_self+1],obj1->point->v[i_self]);
		v2=rotatev2f(v2,obj1->angle);
		normal2=normalizev2f(vec3f_to_vec2f(crossf(vec3f(0,0,1),vec2f_to_vec3f(v2))));
		
		
		obj1->pos=addv2f(obj1->pos,scalev2f(normal2,positional_impulse));
		
		perpendicular_size=dotv2f(scalev2f(relative_vel,-1),normal2)*(bounce+1);
		perpendicular_vel=scalev2f(normal2,perpendicular_size);

		irregularApplyImpulse(obj1,normal2,force*perpendicular_size);
		
		friction=addv2f(obj1->vel,perpendicular_vel);
		
		if(lengthv2f(friction)>x)
		{
			friction=normalizev2f(friction);
			friction=scalev2f(friction,-x);
		
			obj1->vel=addv2f(obj1->vel,friction);
		}
		else
		{
			friction=scalev2f(friction,-1);
		
			obj1->vel=addv2f(obj1->vel,friction);
		}
		
	}
	else if(i_other!=-1)
	{
		i_point=irregularPointSelf(obj1,obj2);
		point=obj1->point->v[i_point];
		point=rotatev2f(point,obj1->angle);
		point=addv2f(point,obj1->pos);
		
		v1=subv2f(obj2->point->v[i_other+1],obj2->point->v[i_other]);
		v1=rotatev2f(v1,obj2->angle);
		normal1=normalizev2f(vec3f_to_vec2f(crossf(vec2f_to_vec3f(v1),vec3f(0,0,1))));
		
		obj1->pos=addv2f(obj1->pos,scalev2f(normal1,positional_impulse));
		
		perpendicular_size=dotv2f(scalev2f(relative_vel,-1),normal1)*(bounce+1);
		perpendicular_vel=scalev2f(normal1,perpendicular_size);
		
		irregularApplyImpulse(obj1,normal1,force*perpendicular_size);
		
		friction=addv2f(obj1->vel,perpendicular_vel);
		
		if(lengthv2f(friction)>x)
		{
			friction=normalizev2f(friction);
			friction=scalev2f(friction,-x);
		
			obj1->vel=addv2f(obj1->vel,friction);
		}
		else
		{
			friction=scalev2f(friction,-1);
		
			obj1->vel=addv2f(obj1->vel,friction);
		}
	}
}

void irregularBounce(irregular *obj1,irregular *obj2,float positional_impulse,float bounce)
{
	float perpendicular_size;
	vector2f relative_vel,perpendicular_vel;
	vector2f v1,v2;
	vector2f normal1,normal2;
	int i_self,i_other,i_point;
	vector2f point;
	i_self=irregularLineSelf(obj1,obj2);
	i_other=irregularLineOther(obj1,obj2);
	
	relative_vel=subv2f(obj1->vel,obj2->vel);
	
	if(i_self!=-1 && i_other!=-1)
	return;
	if(i_other!=-1)
	{
		i_point=irregularPointSelf(obj1,obj2);
		point=obj1->point->v[i_point];
		point=rotatev2f(point,obj1->angle);
		point=addv2f(point,obj1->pos);
		
		v1=subv2f(obj2->point->v[i_other+1],obj2->point->v[i_other]);
		v1=rotatev2f(v1,obj2->angle);
		normal1=normalizev2f(vec3f_to_vec2f(crossf(vec2f_to_vec3f(v1),vec3f(0,0,1))));
		
		obj1->pos=addv2f(obj1->pos,scalev2f(normal1,positional_impulse));
		
		perpendicular_size=dotv2f(scalev2f(relative_vel,-1),normal1)*(bounce+1);
		perpendicular_vel=scalev2f(normal1,perpendicular_size);
		
		obj1->vel=addv2f(obj1->vel,perpendicular_vel);
	}
	else if(i_self!=-1)
	{
		i_point=irregularPointOther(obj1,obj2);
		point=obj2->point->v[i_point];
		point=rotatev2f(point,obj2->angle);
		point=addv2f(point,obj2->pos);
		
		v2=subv2f(obj1->point->v[i_self+1],obj1->point->v[i_self]);
		v2=rotatev2f(v2,obj1->angle);
		normal2=normalizev2f(vec3f_to_vec2f(crossf(vec3f(0,0,1),vec2f_to_vec3f(v2))));
		
		obj1->pos=addv2f(obj1->pos,scalev2f(normal2,positional_impulse));
			
		perpendicular_size=dotv2f(scalev2f(relative_vel,-1),normal2)*(bounce+1);
		perpendicular_vel=scalev2f(normal2,perpendicular_size);

		obj1->vel=addv2f(obj1->vel,perpendicular_vel);
	}
}


void irregularUpdate(irregular *obj,float limit_speed,float limit_rotational_speed)
{
	obj->dir=getAnglev2f(obj->vel);
	obj->sp=lengthv2f(obj->vel);
	
	if(obj->sp>limit_speed)
		irregularSetSpeed(obj,limit_speed);
	
	if(obj->angular_vel> obj->rotational_speed_limit*limit_rotational_speed)
	   obj->angular_vel= obj->rotational_speed_limit*limit_rotational_speed;
    if(obj->angular_vel<-obj->rotational_speed_limit*limit_rotational_speed)
	   obj->angular_vel=-obj->rotational_speed_limit*limit_rotational_speed;
	
	
	obj->pos.e[0]+=obj->vel.e[0];
	obj->pos.e[1]+=obj->vel.e[1];
	
	obj->angle+=obj->angular_vel;
}

void irregularDraw(irregular *obj)
{
	vector2f p,p1,p2;
	int i;
	for(i=0; i<obj->point->n-1; i++)
	{
		p1=obj->point->v[i];
		p2=obj->point->v[i+1];
		p1=rotatev2f(p1,obj->angle);
		p2=rotatev2f(p2,obj->angle);
		p1=addv2f(p1,obj->pos);
		p2=addv2f(p2,obj->pos);
		
		drawThickLinefHW(p1,p2,obj->margin/2);
	}
	for(i=0; i<obj->point->n; i++)
	{
		p=obj->point->v[i];
		p=rotatev2f(p,obj->angle);
		p=addv2f(p,obj->pos);
		
		drawCirclefHW(p,obj->margin/2);
	}
}

#endif
