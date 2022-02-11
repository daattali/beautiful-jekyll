---
layout: page
permalink: /Multiscale_image_registration/
subtitle: Multiscale image registration
---

This page supplements our paper on multiscale atlas estimation. Below are displayed movies showing the estimation of template images using either the <a href="https://hal.inria.fr/hal-00817565 ">original algorithm</a>, either our coarse-to-fine strategy, with varying numbers of control points. In all cases, atlas estimation was performed using the same set of 20 images.

### Atlas estimation on digit images from the MNIST handwritten digits database

 <a href="http://yann.lecun.com/exdb/mnist/">Link to the MNIST database</a>

<table>
<tr>
   <th> Number of control points </th>

<th>  <img width=100/> Original   <img width=100/></th>
<th> <img width=100/>Coarse-to-fine  <img width=100/> </th>
</tr>
   
   <tr>
<td>49</td>
    
<td>
   <center>
<img src="/assets/img/digit_no_ctf_k4_fold_5.gif" alt="drawing" width="100"/>
   </center>
</td>
<td>   
<center><img src="/assets/img/digit_ctf_cv_k4_fold_5.gif" alt="drawing" width="100"/></center>
</td>
 
</tr>
 
 
  <tr>
 <td>100</td>

<td>
<center><img src="/assets/img/digit_no_ctf_k3_fold_5.gif" alt="drawing" width="100"/></center>
</td>
<td>
<center><img src="/assets/img/digit_ctf_cv_k3_fold_5.gif" alt="drawing" width="100"/></center>
</td>
 
</tr>

   <tr>
      <td>196</td>
 
<td>
<center><img src="/assets/img/digit_no_ctf_k2_fold_5.gif" alt="drawing" width="100"/></center>
</td>
<td>
<center><img src="/assets/img/digit_ctf_cv_k2_fold_5.gif" alt="drawing" width="100"/></center>
</td>
 
</tr>
 
 
 <tr>
   <td>361</td>
 
<td>
<center><img src="/assets/img/digit_no_ctf_k1.5_fold_5.gif" alt="drawing" width="100"/></center>
</td>
<td>
<center><img src="/assets/img/digit_ctf_cv_k1.5_fold_5.gif" alt="drawing" width="100"/></center>
</td>
 
</tr> 
</table>

 ### Atlas estimation on images of artificial characters
 
 <a id="raw-url" href="https://github.com/fleurgaudfernau/fleurgaudfernau.github.io/raw/master/assets/img/characters.zip" download>Click here to download the dataset</a>
 
<table>
<tr>
   <th> Number of control points </th>

<th><img width=100/>Original <img width=100/> </th>
<th><img width=100/>Coarse-to-fine <img width=100/> </th>
</tr>
   
    <tr>
   <td>36</td>
 
<td>
<center><img src="/assets/img/bonhommes_no_ctf_k5_fold_1.gif" alt="drawing" width="100"/></center>
</td>
<td>
<center><img src="/assets/img/bonhommes_ctf_k5_fold_1.gif" alt="drawing" width="100"/></center>
</td>
 
</tr>

   
   <tr>
<td>49</td>
    
<td>
<center><img src="/assets/img/bonhommes_no_ctf_k4_fold_1.gif" alt="drawing" width="100"/></center>
</td>
<td>
<center><img src="/assets/img/bonhommes_ctf_k4_fold_1.gif" alt="drawing" width="100"/></center>
</td>
 
</tr>
 
 
  <tr>
 <td>100</td>

<td>
<center><img src="/assets/img/bonhommes_no_ctf_k3_fold_1.gif" alt="drawing" width="100"/></center>
</td>
<td>
<center><img src="/assets/img/bonhommes_ctf_k3_fold_1.gif" alt="drawing" width="100"/></center>
</td>
 
</tr>

   <tr>
      <td>196</td>
 
<td>
<center><img src="/assets/img/bonhommes_no_ctf_k2_fold_1.gif" alt="drawing" width="100"/></center>
</td>
<td>
<center><img src="/assets/img/bonhommes_ctf_k2_fold_1.gif" alt="drawing" width="100"/></center>
</td>
 
</tr>

</table>



 


