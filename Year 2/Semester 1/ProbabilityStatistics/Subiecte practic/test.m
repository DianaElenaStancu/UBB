function test(N=10000)
  #{
  urna=['r','r','r','r','r','r','r','r','r','r','n','n','n','n','n','a','a','a','a','a'];
  fa=0; fb=0; fac=0; fc=0;
  for i=1:N
    extragere=randsample(urna, 4);
    if length(unique(extragere)) == 1
      ++fa;
      if extragere(1) == 'n'
        ++fac;
      endif
    endif
    if length(unique(extragere)) == 3
      ++fb;
    endif
    if extragere(1) == 'n' || extragere(2) == 'n' || extragere(3) == 'n' || extragere(4) == 'n'
      fc = fc + 1;
    endif
  endfor
  bilele_au_aceeasi_culoare=fa/N
  bilele_au_aceeasi_culoare_TEORETIC = (nchoosek(10,4) + nchoosek(5,4) + nchoosek(5,4))/ nchoosek(20,4)
  extregerea_contine_3_culori_diferite=fb/N
  extregerea_contine_3_culori_diferite_TEORETIC=(nchoosek(10,1)*nchoosek(5,2)*nchoosek(5,1)*2+nchoosek(10,2)*nchoosek(5,1)*nchoosek(5,1))/nchoosek(20,4)
  toate_negre=fac/N
  toate_negre_TEORETIC=nchoosek(5,4)/nchoosek(20,4)
  cel_putin_una_neagra=fc/N
  cel_putin_una_neagra_TEORETIC=1-(nchoosek(5,4)+nchoosek(10,4)+nchoosek(10,1)*nchoosek(5,3)+nchoosek(10,2)*nchoosek(5,2)+nchoosek(10,3)*nchoosek(5,1))/nchoosek(20,4)
  #}


  X=[-2:0.0001:5];
  lambda=2;
  fDens=exppdf(X, 1/lambda);
  figure(1)
  plot(fDens, 'r*');


  fRep=expcdf(X, 1/lambda);

  figure(2)
  plot(fRep, 'y*');


  Y=exprnd(1/lambda, 1, N);
  valoarea_medie=mean(Y)
  abaterea_standard=std(Y)

  p_practic=sum(Y>0.7)/N
  p_teoretic=1 - fRep((0.7 - (-2) )/0.0001 )
  p_teoretic_destept=1-expcdf(0.7, 1/lambda)

#{
  x = [];
  for i = 1:50000
    a=rand();
    if a<=0.1
      x=[x -2];
    elseif a<=0.5
      x=[x -1];
    elseif a<=0.8
      x=[x 1];
    else
      x=[x 2];
    endif
  endfor


  xx=randsample([-2 -1 1 2], 50000, replacement = true, [0.1 0.4 0.3 0.2]);

  y = unifrnd(-1,4,1,50000);
  u = x.^3 - y.^3;

  hist(u,20)
  mean(u)
  std(u)
  sum(u < 0) / 50000
  mean(x.^3)
#}
  #{
  v.a. y~N(0,1), se genereaza 1000 de valori aleatoare
  a si b P(y^2 < 0.25) est si teor
  c histograma cu 13 bare cu frecv relative + functia de densitate a lui y
  #}

  #{
  N=100000;
  Y=normrnd(0, 1, 1, N);
  Y_patrat=Y.^2;
  practic=sum(Y_patrat < 0.25)/N #sau mean(Y_patrat<0.25)
  teoretic=normcdf(0.5, 0,1)-normcdf(-0.5, 0, 1)


  [~, mijl]=hist(Y, 13)
  mijl
  l=(max(Y)-min(Y))/13;
  hist(Y, mijl, 1/l)
  hold on
  fDens=@(Y) normpdf(Y, 0, 1);
  fplot(fDens, [min(Y), max(Y)], '-m')
  #}
  #{
    N=100000;
  Y=exprnd(1, 1, N);
  practic=sum(Y > 0.5)/N #sau mean(Y_patrat<0.25)
  teoretic=1-expcdf(0.5, 1)


  [~, mijl]=hist(Y, 12);
  mijl;
  l=(max(Y)-min(Y))/12;
  hist(Y, mijl, 1/l)
  hold on
  fDens=@(Y) normpdf(Y, 0, 1);
  fplot(fDens, [min(Y), max(Y)], '-m')
  #}

end
