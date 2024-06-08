import numpy as np
import matplotlib.pyplot as plt

MAX_INTERVAL_WIDTH = 3

def realRootsEllipticCurve(a,b):
    coeff=[1,0,a,b]
    roots= [np.real(r) for r in np.roots(coeff) if np.isreal(r)]
    roots.sort()
    return roots

def getPlotIntervals(a, b, points, extraSpace=1):
    points_x = [x[0] for x in points]
    roots_x = realRootsEllipticCurve(a,b)
    total_points_x = points_x + roots_x
    MIN_X = np.min(total_points_x) - extraSpace
    MAX_X = np.max(total_points_x) + extraSpace

    images = [np.sqrt(p*p*p +a*p +b) for p in points_x] + [0]
    MIN_Y = -np.max(images)-extraSpace
    MAX_Y = np.max(images) +extraSpace
    return [[MIN_X,MAX_X],[MIN_Y,MAX_Y]]


def generateRandomPoint(a,b):
    roots = realRootsEllipticCurve(a,b)
    if len(roots) == 1:
        total_length = MAX_INTERVAL_WIDTH-roots[0]
    if len(roots) == 3:
        total_length = roots[1]-roots[0]+MAX_INTERVAL_WIDTH
    
    while (True):
        x = np.random.random()*total_length
        x += roots[0]
        if len(roots) == 3 and x > roots[1]: x = roots[2]-roots[1]
        if x*x*x+a*x+b < 0: 
            continue
        else: 
            break

    if np.random.random() > 0.5: y = -np.sqrt(x*x*x +a*x +b)
    else: y = np.sqrt(x*x*x +a*x +b) 
    return [x,y]

def sumPoints(P,Q):
    m = (Q[1]-P[1])/(Q[0]-P[0])
    c = P[1]-m*P[0]
    x = m*m - P[0]-Q[0]
    y = m*x + c 
    return [x,-y]

def representPoint(P,text):
    plt.plot(P[0],P[1],"ro")
    plt.text(P[0],P[1],text)
    print(text,P[0],P[1])

def plotEllipticCurve(a, b, arrayPoints,box_text):
    x = getPlotIntervals(a,b,arrayPoints)[0]
    y = getPlotIntervals(a,b,arrayPoints)[1]
    plt.text(x[0],y[1], box_text, ha='center', va='center', bbox=dict(boxstyle = "square", facecolor = "white"))
    y, x = np.ogrid[y[0]:y[1]:100j, x[0]:x[1]:100j]
    plt.contour(x.ravel(), y.ravel(), pow(y, 2) - pow(x, 3) - x * a - b, [0])


a,b = 0,0
while 4*a*a*a+27*b*b==0:
    a = float(input("Enter the value of a: "))
    b = float(input("Enter the value of b: "))

box_text = ""
P = generateRandomPoint(a, b)
representPoint(P,'P')
box_text += "P({},{})\n".format(np.round(P[0],3),np.round(P[1],3))

Q = generateRandomPoint(a, b)

while Q[0]-Q[1]== 0 or P[0]==Q[0] and P[1]==Q[1]:
    Q = generateRandomPoint(a, b)
representPoint(Q,'Q')
box_text += "Q({},{})\n".format(np.round(Q[0],3),np.round(Q[1],3))

sum = sumPoints(P,Q)
representPoint(sum,'P+Q')
box_text += "P+Q({},{})\n".format(np.round(sum[0],3),np.round(sum[1],3))
oppositeP = [P[0],-P[1]]
representPoint(oppositeP,'-P')
box_text += "-P({},{})".format(np.round(P[0],3),np.round(-P[1],3))

points = [P,Q,sum,oppositeP]

plotEllipticCurve(a,b,points,box_text)

plt.grid() 
plt.show()