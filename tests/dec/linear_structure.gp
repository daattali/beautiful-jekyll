set terminal qt 0
set title "neumann boundary condition"
plot "linear_structure_neumann.dat" using 1 title "numerical" with lines, "linear_structure_neumann.dat" using 2 title "analytical" with lines

set terminal qt 1
set title "dirichlet boundary condition"
plot "linear_structure_dirichlet.dat" using 1 title "numerical" with lines, "linear_structure_dirichlet.dat" using 2 title "analytical" with lines
