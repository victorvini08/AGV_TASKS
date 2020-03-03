from math import *
import matplotlib.pyplot as plt
import numpy as np
from numpy.linalg import inv





file = open("kalmann.txt","r")

my_list=file.readlines()

result=[]
for i in range(len(my_list)):

	result.append([x.strip() for x in my_list[i].split(',')])


t=float(input("Enter time step:"))
print(t)	



#print(result)
n=len(my_list)

x=[]
y=[]
vx=[]
vy=[]
for i in range(n):

	if i!=0:

		x.append(float(result[i][0]))
		y.append(float(result[i][1]))
		vx.append(float(result[i][2]))
		vy.append(float(result[i][3]))



x_initial=float(result[0][0])
y_initial=float(result[0][1])


x_observations=np.array(x)
y_observations=np.array(y)
vx_observations=np.array(vx)
vy_observations=np.array(vy)


z = np.c_[x_observations,y_observations]



x=np.array([x_initial,y_initial, 0,6.361599147637872])
x=x.reshape(4,1)


P=np.array([[1,0,0,0],[0,1,0,0],[0,0,700,0],[0,0,0,700]])
print(x)
print(t)

R = np.matrix([[t,0.],[0.,t]])

I = np.matrix([[1., 0.,0.,0.], [0., 1.,0.,0.],[0.,0.,1.,0.],[0.,0.,0.,1.]])

F = np.matrix([[1., 0.,t,0.], [0., 1.,0.,t],[0.,0.,1.,0.],[0.,0.,0.,1.]])

H = np.matrix([[1., 0.,0.,0.],[0.,1.,0.,0.]])

def predict(x, P):
    x = np.matrix(np.dot(F , x))
    P = np.dot(np.dot(F , P) , F.transpose())
     
    #print(x)
    return x,P


def update(x, P,z):
    
    Z = z.reshape(1,2)
    y = Z.transpose() - np.dot(H,x)
    S = np.matrix(np.dot(np.dot(H ,P),H.transpose()) + R)
    K = np.matrix(np.dot(np.dot(P , H.transpose()) , np.linalg.inv(S)))
    x = np.matrix(x + np.matrix(np.dot(K , y)))
    P =np.matrix(np.dot(  P,(I - np.dot(K , H))))
    #print(x)
    return x, P


plotting_x=[]
plotting_y=[]
for measurement in z:
    x,P = predict(x, P)
    x,P = update(x, P,measurement)

    #print(x.shape)
    plotting_x.append(x[0,0])
    plotting_y.append(x[1,0])

    #print(x)
    #print('\n\n')
    #print(P)
    #print('\n\n')
    #break
#print(plotting_x)
#print('\n\n')
#print(plotting_y)
#print('\n\n')
plt.plot(plotting_x,plotting_y,'r--')
plt.plot(x_observations,y_observations,'bs')
plt.show()


   










#print(my_list)

#print(len(my_list))

#def update()

file.close()