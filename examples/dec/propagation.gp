set multiplot layout 2,2
set title "horizontal"
plot [-1:1] for [i=0:5] "propagation_forced_samples_hv_".i.".dat" using 1:2 title "".i with lines
set title "vertical"
plot [-1:1] for [i=0:5] "propagation_forced_samples_hv_".i.".dat" using 1:3 title "".i with lines
set title "positive diag"
plot [-1:1] for [i=0:5] "propagation_forced_samples_diag_".i.".dat" using 1:2 title "".i with lines
set title "negative diag"
plot [-1:1] for [i=0:5] "propagation_forced_samples_diag_".i.".dat" using 1:3 title "".i with lines


