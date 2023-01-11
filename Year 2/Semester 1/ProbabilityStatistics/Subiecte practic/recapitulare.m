function recapitulare()
#afiseaza toate aranjamentele de n luate cate k
#{
v=1:5;
n=5;
k=2;
v=nchoosek(v, k);
aranjamente=[];
for i=1:length(v)
   aranjamente=[aranjamente; perms(v(i,:))];
endfor
aranjamente
#}

#23 de persoane sa aiba ziua de nastere in aceeasi zi
#{
N=1000;
frecv=0;
for i=1:N
  zile=randi(365, 1, 23);
  if length(unique(zile)) < 23
    ++frecv;
  endif
endfor
rasp=frecv/N
#}
#{
#generare de puncte intr-un patrat
#i) puncte in int patratului
#ii) puncte mai apropiate de centru decat de varfuri
#iii) puncte care formeaza cu varfurile patratelor dou triungh. ascutitungice si 2 obtuzungice
clf;hold on;axis square;axis off;
rectangle('Position', [0 0 1 1])
N=1000;
frecv=0;
for i=1:N
  x=rand;
  y=rand;
  #if pdist([x y;0.5 0.5]) <= 0.5 #i
  #if pdist([x y;0.5 0.5]) <= pdist([x y;0 0]) && pdist([x y;0.5 0.5]) <= pdist([x y;1 1]) && pdist([x y;0.5 0.5]) <= pdist([x y;1 0]) && pdist([x y;0.5 0.5]) <= pdist([x y;0 1])
  AP=pdist([x y;0 0]);
  BP=pdist([x y;1 1]);
  CP=pdist([x y;0 1]);
  DP=pdist([x y;1 0]);
  obtuz=0;
  if AP^2+CP^2 > 1
    obtuz++;
  endif
  if BP^2+DP^2 > 1
    obtuz++;
  endif
  if CP^2+BP^2 > 1
    obtuz++;
  endif
  if DP^2+AP^2 > 1
    obtuz++;
  endif
  if obtuz==2
    plot(x, y,'dm','MarkerSize',7,'MarkerFaceColor','m');
    frecv++;
  endif
endfor
rasp=frecv/N
#}
#{
urna=['r', 'r', 'r', 'r', 'r' 'a', 'a', 'a', 'v', 'v'];
cont=0;
for i=1:5000
  ext=randsample(urna, 3);
  if ext(1)=='r' && ext(2)=='r' && ext(3)=='r'
    ++cont;
  endif
endfor
rasp=cont/5000
#}
#{
2lab3
clf;grid on; hold on;
n=5; p=1/3; nr_sim=5000;

x=binornd(n,p,1,nr_sim);
N=hist(x,0:n);
bar(0:n,N/nr_sim,'hist','FaceColor','b');#pt fiecare element se creeaza o bara cu probabilitatea in momentul respectiv
bar(0:n,binopdf(0:n,n,p),'FaceColor','y');#asta e cea teoretica
legend('probabilitatile estimate','probabilitatile teroretice');

set(findobj('type','patch'),'facealpha',0.7);xlim([-1 n+1]);
#}
#{
m=1000;
disp('i)')
sume_posibile=4:24;
zaruri=randi(6,4,m);
sume_sim=sum(zaruri);
frecv_abs=hist(sume_sim,sume_posibile);
sume_frecv_abs=[sume_posibile;frecv_abs]'
disp('ii)')
clf;hold on;grid on;
xticks(sume_posibile);xlim([3,25]);
yticks(0:0.01:0.14);ylim([0 0.14]);
bar(sume_posibile,frecv_abs/m,'hist','FaceColor','b');
frecv_abs_max=max(frecv_abs)
sume_cele_mai_frecvente=sume_posibile(frecv_abs==frecv_abs_max)
#}
n = 50;
X = normrnd(165, 10, n, 1);
figure(1);
hist(X)
minVal = min(X)
maxVal = max(X)
baseWidth = (maxVal - minVal)/10
figure(2);
hold on;
hist(X, 10, 1/baseWidth)
kSegments = n/4
x = linspace(minVal, maxVal, kSegments);
y = normpdf(x, 165, 10);
plot(x, y, 'r');
leftBorder = 160;
rightBorder = 170;
Xinterval = [];
for i=1:n
  if X(i) >= 160 && X(i) <= 170
    Xinterval(end + 1) = X(i);
  endif
endfor
Xinterval
medianValue = mean(Xinterval)
standardDeviation = std(Xinterval)

end

