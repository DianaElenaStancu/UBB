function test2(N=10000)
  #{
X = [1 2 3];
  p = [10/20 5/20 5/20];
  ac = 0;
  dist = 0;
  for i=1:N
    Y = randsample(X, 4, true, p);
    r = sum((Y == 1));
    n = sum((Y == 2));
    a = sum((Y == 3));
    if r == 4 || n == 4 || a == 4
      ac++;
    endif
    if r >= 1 && n >= 1 && a >= 1
      dist++;
    endif
   endfor
  printf("Probabilitatea practica de a avea acceasi culoare = %d\n", ac/N)
  # extragem 4 rosii SAU 4 albe SAU 4 negre
  p = (nchoosek(10,4) + nchoosek(5,4) + nchoosek(5,4))/ nchoosek(20,4);
  printf("Probabilitatea teorietic de a avea acceasi culoare = %d\n",p)
  # 2 1 1 || 1 2 1 || 1 1 2  / nchoosek(20,4)
  p2 = (nchoosek(10,2) + nchoosek(5,1) * 2 + nchoosek(10,1) + nchoosek(5,2) + nchoosek(5,1) + nchoosek(10,1) + nchoosek(5,1) + nchoosek(5,2))/nchoosek(20,4);
  printf("Probabilitatea practica de a avea culoari distincte = %d\n", dist/N)
  printf("Probabilitatea teoretica de a avea culoari distincte = %d\n", p2)
  printf("Probabilitatea practica  ca bilele sa nu aiba aceasi culoare=%d\n", 1 - ac/N)
  printf("Probabilitatea teoretica ca bilele sa nu aiba aceasi culoare=%d\n", 1 - p)
  #}

  #{
  #frecv rel cu 13 clase + fct de densitate
  x = normrnd(0, 1, 1, N);
  hist(x, 13);
  [~, mijl] = hist(x, 13);
  l = (max(x)-min(x))/13;
  hist(x, mijl, 1/l);
  f=@(y) normpdf(y, 0, 1);
  hold on;
  fplot(f, [min(x), max(x)], '-m');

  #P(Y^2<0,25) = P(-0.5 < Y < 0.5) = P((Y > 0.5) & (Y < 0.5)) =F(0.5) - F(-0.5)
  p = sum((x < 0.5) & (x > -0.5))/N;
  disp("prob estimata");
  disp(p);

  disp("prob teor");
  pt = normcdf(0.5, 0, 1) - normcdf(-0.5, 0, 1);
  disp(pt);
  #}


    pkg load statistics
  nr = 0;
  for i= 1:N
    % valoare din distributia exponentiala cu lambda = 1/1
    x = exprnd(1);
    % nr cazuri favorabile
    if x > 0.5
      nr++;
    endif
  endfor
  pA = nr/N
  % expcdf calculeaza P(X<0.5), deci ne trebuie 1-P(X>0.5)
  pA_teoretic = 1 - expcdf(0.5,1)

    pkg load statistics
  %vector cu N valori din distributia exponentiala cu lambda = 1/1
  x=exprnd(1,1,N);

  %xx - vector cu mijloacele barelor
  [~,xx]=hist(x,12);

  %afisam histograma frcventelor relative cu 12 bare
  hist(x,xx,12/(max(x)-min(x)));

  hold on;

  %vector cu N puncte egal distantate intre min(x) si max(x)
  t=linspace(min(x),max(x),N);

  %exppdf calculeaza f(x) - functia de densitate in toate punctele vectorului t
  plot(t,exppdf(t,1),'-r','LineWidth',3);


  figure(2)
      N=100000;
  Y=exprnd(1, 1, N);
  practic=sum(Y > 0.5)/N
  teoretic=1-expcdf(0.5, 1)


  [~, mijl]=hist(Y, 12);
  mijl;
  l=(max(Y)-min(Y))/12;
  hist(Y, mijl, 1/l)
  hold on
  fDens=@(Y) exppdf(Y, 1);
  fplot(fDens, [min(Y), max(Y)], '-m')

endfunction

