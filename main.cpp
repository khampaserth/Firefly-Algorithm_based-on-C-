
/*
This Firefly algorithm program is original by Mr Alam. and I adding more fitness function for
 test three benchmark function optimization in order to reached zeros values. 
*/

#include <iostream>
#include "itpp/itbase.h"

using namespace std;
using namespace itpp;

#define minValue -5.12
#define maxValue 5.12
#define ff_num 20
#define dim_ 300
#define max_iter 50

//Function
double calculate_fitness_sphere(vec ff_pos)
{
    int dim = ff_pos.length();
    double fitness =0.0;
    for (int i=0; i<dim; i++)
    {
        double xi=ff_pos(i);
        fitness += xi*xi;
    }
    return fitness;
}

double calculate_fitness_Rastrigin(vec ff_pos)
{
    int dim = ff_pos.length();
    double fitness =0.0;
    for (int i=0; i<dim; i++)
    {
        double xi=ff_pos(i);
        fitness += (xi*xi)-(10*cos(2*M_PI*xi))+10;
    }
    return fitness;
}

double rosenbrock(vec ff_pos)
{
    int dim = ff_pos.length();
    double fitness=0.0;
    for (int i=0; i<dim-1; i++)
    {
        double xi=ff_pos(i);
        double xnext=ff_pos(i+1);
        fitness+=100*(xnext-xi*xi)*(xnext-xi*xi)+(xi-1)*(xi-1);
    }
    return fitness;
}


vec create_firefly(int dim)
{
    vec ff_pos(dim);
    for (int i=0; i<dim; i++)
    {
          ff_pos(i)=(maxValue-minValue)*randu()+minValue;
    }
       return ff_pos;
}

double calc_distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

mat cal_distanceRB(mat x)
{
    double result_dis=.0;
    mat result = zeros(x.rows(),1);

    for (int i=0;i<x.rows();i++)
    {
        for (int j=0;j<5;j++)
        {
          result_dis +=pow((x(0,j)-x(i+1,j)),2);
        }
        result.set(i,0,sqrt(result_dis));
    }
    return result;

}


int main(int argc, char*const argv[])
{

ofstream FF;
   int dim =dim_;
   int S = ff_num;
   mat ff_pos(S,dim_);
   vec ff_fitvalue(S);
   double best_fitness;
   int best_id;
   double dist;

//======= Test the accuracy of the function
   vec Firefly_Al="0,0";
//cout<<"Sphere=   "    <<calculate_fitness_sphere(Firefly_Al)<<endl;
//cout<<"Rastrigin=   "<<calculate_fitness_Rastrigin(Firefly_Al)<<endl;
//cout<<"Rosenbrock=   "<<rosenbrock(Firefly_Al)<<endl<<endl;

//========

   //input attraction parameter
   double gamma_ =1.0;
   double alpha_ = 0.2;
   double beta_0 = 1.0;

   //Initial firefly position
   for(int n=0; n<S; n++)
   {
     vec new_ff = create_firefly(dim);
     ff_pos.set_row(n,new_ff);

       ff_fitvalue(n) = calculate_fitness_sphere(new_ff);
     //ff_fitvalue(n) = calculate_fitness_Rastrigin(new_ff);
     //ff_fitvalue(n) = rosenbrock(new_ff);
   }
   //cout<<ff_pos<<endl;

//FirstLocation
/*
//FF.open("FF_First_position.txt");
//   FF<<ff_pos<<endl;
//FF.close();

//Start of iteration
*/
//Output
    FF.open("Fitness_value_sphere.txt");
    //FF.open("Fitness_value_Rast.txt");
    //FF.open("Fitness_value_rosenbrock.txt");

     //FF.open("Fitness_value_location.txt");


for (int iter=0; iter<max_iter; iter++)
{

    best_fitness = ff_fitvalue(0);
    for(int n=0; n<S; n++)
    {
        if (ff_fitvalue(n) < best_fitness)
        {
            best_fitness = ff_fitvalue(n);
            best_id = n;
        }

    }

	//cout << "Best fitness at iter-" << iter << " = " << best_fitness << " at " << ff_pos.get_row(best_id)<<" id"<<best_id<<endl;

    FF<<iter<<" "<<best_fitness<<endl;
    //FF<<ff_pos.get_row(best_id)<<endl;



		//Move each firefly toward the bester one
       for (int n=0; n<S; n++)
       {
           for (int n2=0; n2<S; n2++)
           {
               dist = calc_distance(ff_pos(n,0),ff_pos(n,1),ff_pos(n2,0),ff_pos(n2,1));
			   cout<<dist<<endl;

				// set condition in order to move Firefly to the best one

               if (ff_fitvalue(n2) < ff_fitvalue(n))
               {
                   double beta=beta_0*exp((-gamma_)*dist*dist);
                   for (int t=0; t<dim; t++)
                   {


                    ff_pos(n,t)= ff_pos(n,t) + beta*ff_pos(n2,t)-beta*ff_pos(n,t)+alpha_*(randu()-0.5);  //refer to Yang_nature book e(i)=rand -1/2;

                    //Set limit movement of firefly for inside area

                    if (ff_pos(n,t) < minValue)
                    {
                        ff_pos(n,t) = minValue;
                    }
                    if (ff_pos(n,t) > maxValue)
                    {
                        ff_pos(n,t) = maxValue;
                    }
                  }

            //calculate fitness at new position

                  ff_fitvalue(n) = calculate_fitness_sphere(ff_pos.get_row(n));
              //     ff_fitvalue(n) = calculate_fitness_Rastrigin(ff_pos.get_row(n));
              //    ff_fitvalue(n) = rosenbrock(ff_pos.get_row(n));
               }
				//cout<<"distance"<<"\t"<<dist<<endl;
           }
       }
}

//Output
FF.close();

	vec random_x;
	vec yy="2 4.5 1 6 3";
	random_x =concat(random_x,yy);
	//cout<<"random oftimization=  "<<random_x<<endl;

	mat x="2 4 6 8 10;2 6 4 8 2; 4 2 8 10 14";
	mat y = zeros(x.rows(),1);
	y = cal_distanceRB(x);


	int jampa(3);
	cout<<"location number"<<"\t"<<jampa<<endl;


}
