function SIM = sim(N=5000)
  SIM = 0;
  urna = ['r', 'r', 'r', 'r',  'r', 'a', 'a', 'a', 'v', 'v'];
  for i = 1:N
    extragere = randsample(urna, 3);
    if (extragere(1) == 'r')
      if (extragere(1) == 'r' && extragere(2) == 'r' && extragere(3) == 'r')
        ++SIM;
      endif
    endif
  endfor
  SIM = SIM/5000;
end
