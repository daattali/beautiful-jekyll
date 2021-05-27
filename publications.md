---
layout: page
title: Publications
subtitle: 
---

<table cellpadding="10" width="100%">

    <tr>
        <td class="pubimg" width="250" height="100">
            <img src="" img width="250">
        </td>
        <td>Active Safety Envelopes using Light Curtains with Probabilistic Guarantees<br>
            <div class="pubauthor">Siddharth Ancha, Gaurav Pathak, Srinivasa Narasimhan, David Held<br>
            </div>
            <div id="bib2021safetyenvelopes" style="display:none">
                <blockquote>
<pre>@INPROCEEDINGS{Ancha-RSS-21,
    AUTHOR    = {Siddharth Ancha AND Gaurav Pathak AND Srinivasa G. Narasimhan AND David Held},
    TITLE     = {Active Safety Envelopes using Light Curtains with Probabilistic Guarantees},
    BOOKTITLE = {Proceedings of Robotics: Science and Systems},
    YEAR      = {2021},
    MONTH     = {July}
}</pre>
                </blockquote>
            </div>
            <div id="abs2021safetyenvelopes" style="display:none">
                <blockquote>
                To safely navigate unknown environments, robots must accurately perceive dynamic obstacles. Instead of directly measuring the scene depth with a LiDAR sensor, we explore the use of a much cheaper and higher resolution sensor: <b>programmable light curtains</b>. Light curtains are controllable depth sensors that sense only along a surface that a user selects.  We use light curtains to estimate the <b>safety envelope</b> of a scene: a hypothetical surface that separates the robot from all obstacles. We show that generating light curtains that sense <b>random</b> locations (from a particular distribution) can quickly discover the safety envelope for scenes with unknown objects. Importantly, we produce theoretical safety guarantees on the probability of detecting an obstacle using random curtains. We combine random curtains with a machine learning based model that forecasts and tracks the motion of the safety envelope efficiently. Our method accurately estimates safety envelopes while providing probabilistic safety guarantees that can be used to certify the efficacy of a robot perception system to detect and avoid dynamic obstacles. We evaluate our approach in a simulated urban driving environment and a real-world environment with moving pedestrians using a light curtain device and show that we can estimate safety envelopes efficiently and effectively.
                </blockquote>
            </div>
            <div class="pubjournal">Robotics: Science and Systems (RSS), 2021
            <div style="font-size:small">
                <!-- <a href="https://bokorn.github.io/zephyr/">[Project Page]</a> -->
                <!-- <a href="https://github.com/Xingyu-Lin/softgym">[Code]</a> -->
                <a href="javascript:copy(div2021safetyenvelopes, bib2021safetyenvelopes)">[Bibtex]</a>
                <a href="javascript:copy(div2021safetyenvelopes, abs2021safetyenvelopes)">[Abstract]</a>
                <!-- <a href="https://bokorn.github.io/zephyr/resources/ZePHyR_Zero-shot_Pose_Hypothesis_Rating.pdf">[PDF]</a> -->
            </div>
            <div id="div2021safetyenvelopes" class="pubInfo"></div>
            </div>
            <br>
        </td>
    </tr>
    <tr>
        <td class="pubimg" width="250" height="100">
            <img src="../pics/zephyr.png" img width="250">
        </td>
        <td><a href="https://arxiv.org/abs/2104.13526">ZePHyR: Zero-shot Pose Hypothesis Rating</a><br>
            <div class="pubauthor">
                Brian Okorn*, Qiao Gu*, Martial Hebert, David Held<br>
            </div>
            <div id="bib2021zephyr" style="display:none">
                <blockquote>
                    <pre>@inproceedings{icra2021zephyr,
                    title={ZePHyR: Zero-shot Pose Hypothesis Rating},
                    author={Brian Okorn, Qiao Gu, Martial Hebert, David Held},
                    booktitle={2021 International Conference on Robotics and Automation (ICRA)},
                    year={2021}}</pre>
                </blockquote>
            </div>
            <div id="abs2021zephyr" style="display:none">
                <blockquote>
                    Pose estimation is a basic module in many robot manipulation pipelines. Estimating the pose of objects in the environment can be useful for grasping, motion planning, or manipulation. However, current state-of-the-art methods for pose estimation either rely on large annotated training sets or simulated data. Further, the long training times for these methods prohibit quick interaction with novel objects. To address these issues, we introduce a novel method for zero-shot object pose estimation in clutter. Our approach uses a hypothesis generation and scoring framework, with a focus on learning a scoring function that generalizes to objects not used for training. We achieve zero-shot generalization by rating hypotheses as a function of unordered point differences. We evaluate our method on challenging datasets with both textured and untextured objects in cluttered scenes and demonstrate that our method significantly outperforms previous methods on this task. We also demonstrate how our system can be used by quickly scanning and building a model of a novel object, which can immediately be used by our method for pose estimation. Our work allows users to estimate the pose of novel objects without requiring any retraining.
                </blockquote>
            </div>
            <div class="pubjournal">International Conference of Robotics and Automation (ICRA), 2021
            <div style="font-size:small">
                <a href="https://bokorn.github.io/zephyr/">[Project Page]</a>
                <a href="https://github.com/r-pad/zephyr">[Code]</a>
                <a href="javascript:copy(div2021zephyr, bib2021zephyr)">[Bibtex]</a>
                <a href="javascript:copy(div2021zephyr, abs2021zephyr)">[Abstract]</a>
                <a href="https://arxiv.org/pdf/2104.13526.pdf">[PDF]</a>
            </div>
            <div id="div2021zephyr" class="pubInfo"></div>
            </div>
            <br>
        </td>
    </tr>
    
    <tr>
        <td class="pubimg" width="250" height="100">
            <img src="" img width="250">
        </td>
        <td>Exploiting & Refining Depth Distributions with Triangulation Light Curtains<br>
            <div class="pubauthor">Yaadhav Raaj, Siddharth Ancha, Robert Tamburo, David Held, Srinivasa Narasimhan<br>
            </div>
            <div id="bib2021exploiting" style="display:none">
                <blockquote>
                    <pre>@inproceedings{cvpr2021raajexploiting,
                    title={Exploiting & Refining Depth Distributions with Triangulation Light Curtains},
                    author={Yaadhav Raaj, Siddharth Ancha, Robert Tamburo, David Held, Srinivasa Narasimhan},
                    booktitle={Proceedings of the IEEE/CVF Conference on Computer Vision and Pattern Recognition (CVPR)},
                    year={2021}}</pre>
                </blockquote>
            </div>
            <div id="abs2021exploiting" style="display:none">
                <blockquote>
                Active sensing through the use of Adaptive Depth Sensors is a nascent field, with potential in areas such as Advanced driver-assistance systems (ADAS). They do however require dynamically driving a laser / light-source to a specific location to capture information, with one such class of sensor being the Triangulation Light Curtains (LC). In this work, we introduce a novel approach that exploits prior depth distributions from RGB cameras to drive a Light Curtain's laser line to regions of uncertainty to get new measurements. These measurements are utilized such that depth uncertainty is reduced and errors get corrected recursively. We show real-world experiments that validate our approach in outdoor and driving settings, and demonstrate qualitative and quantitative improvements in depth RMSE when RGB cameras are used in tandem with a Light Curtain.
                </blockquote>
            </div>
            <div class="pubjournal">Conference on Computer Vision and Pattern Recognition (CVPR), 2021
            <div style="font-size:small">
                <!-- <a href="https://bokorn.github.io/zephyr/">[Project Page]</a> -->
                <!-- <a href="https://github.com/Xingyu-Lin/softgym">[Code]</a> -->
                <a href="javascript:copy(div2021exploiting, bib2021exploiting)">[Bibtex]</a>
                <a href="javascript:copy(div2021exploiting, abs2021exploiting)">[Abstract]</a>
                <!-- <a href="https://bokorn.github.io/zephyr/resources/ZePHyR_Zero-shot_Pose_Hypothesis_Rating.pdf">[PDF]</a> -->
            </div>
            <div id="div2021exploiting" class="pubInfo"></div>
            </div>
            <br>
        </td>
    </tr>
    
    <tr>
        <td class="pubimg" width="250" height="100">
            <img src="" img width="250">
        </td>
        <td>Safe Local Motion Planning with Self-Supervised Freespace Forecasting<br>
            <div class="pubauthor">Peiyun Hu, Aaron Huang, John Dolan, David Held, Deva Ramanan<br>
            </div>
            <div id="bib2021cvpr_safe" style="display:none">
                <blockquote>
                    <pre>@inproceedings{cvpr2021husafe,
                    title={Safe Local Motion Planning with Self-Supervised Freespace Forecasting},
                    author={Peiyun Hu, Aaron Huang, John Dolan, David Held, Deva Ramanan},
                    booktitle={Proceedings of the IEEE/CVF Conference on Computer Vision and Pattern Recognition (CVPR)},
                    year={2021}}</pre>
                </blockquote>
            </div>
            <div id="abs2021cvpr_safe" style="display:none">
                <blockquote>
                Safe local motion planning for autonomous driving in dynamic environments requires forecasting how the scene evolves. Practical autonomy stacks adopt a semantic object-centric representation of a dynamic scene and build object detection, tracking, and prediction modules to solve forecasting. However, training these modules comes at an enormous human cost of manually annotated objects across frames. In this work, we explore future freespace as an alternative representation to support motion planning. Our key intuition is that it is important to avoid straying into occupied space regardless of what is occupying it. Importantly, computing ground-truth future freespace is annotation-free. First, we explore freespace forecasting as a self-supervised learning task. We then demonstrate how to use forecasted freespace to identify collision-prone plans from off-the-shelf motion planners. Finally, we propose future freespace as an additional source of annotation-free supervision. We demonstrate how to integrate such supervision into the learning process of learning-based planners. Experimental results on nuScenes and CARLA suggest both approaches lead to significant reduction in collision rates.
                </blockquote>
            </div>
            <div class="pubjournal">Conference on Computer Vision and Pattern Recognition (CVPR), 2021
            <div style="font-size:small">
                <!-- <a href="https://bokorn.github.io/zephyr/">[Project Page]</a> -->
                <!-- <a href="https://github.com/Xingyu-Lin/softgym">[Code]</a> -->
                <a href="javascript:copy(div2021cvpr_safe, bib2021cvpr_safe)">[Bibtex]</a>
                <a href="javascript:copy(div2021cvpr_safe, abs2021cvpr_safe)">[Abstract]</a>
                <!-- <a href="https://bokorn.github.io/zephyr/resources/ZePHyR_Zero-shot_Pose_Hypothesis_Rating.pdf">[PDF]</a> -->
            </div>
            <div id="div2021cvpr_safe" class="pubInfo"></div>
            </div>
            <br>
        </td>
    </tr>

    <tr>
        <td class="pubimg" width="250" height="100">
            <img src="../pics/corl2020_softgym.png" img width="250">
        </td>
        <td><a href="https://arxiv.org/abs/2011.07215">SoftGym: Benchmarking Deep Reinforcement Learning for Deformable Object Manipulation</a><br>
            <div class="pubauthor">
                Xingyu Lin, Yufei Wang, Jake Olkin, David Held<br>
            </div>
            <div id="bib2020softgym" style="display:none">
                <blockquote>
<pre>@inproceedings{corl2020softgym,
title={SoftGym: Benchmarking Deep Reinforcement Learning for Deformable Object Manipulation},
author={Lin, Xingyu and Wang, Yufei and Olkin, Jake and Held, David},
booktitle={Conference on Robot Learning},
year={2020}}</pre>
                </blockquote>
            </div>
            <div id="abs2020softgym" style="display:none">
                <blockquote>
                    Manipulating deformable objects has long been a challenge in robotics due to its high dimensional state representation and complex dynamics. Recent success in deep reinforcement learning provides a promising direction for learning to manipulate deformable objects with data driven methods. However, existing reinforcement learning benchmarks only cover tasks with direct state observability and simple low-dimensional dynamics or with relatively simple image-based environments, such as those with rigid objects. In this paper, we present SoftGym, a set of open-source simulated benchmarks for manipulating deformable objects, with a standard OpenAI Gym API and a Python interface for creating new environments. Our benchmark will enable reproducible research in this important area. Further, we evaluate a variety of algorithms on these tasks and highlight challenges for reinforcement learning algorithms, including dealing with a state representation that has a high intrinsic dimensionality and is partially observable. The experiments and analysis indicate the strengths and limitations of existing methods in the context of deformable object manipulation that can help point the way forward for future methods development. Code and videos of the learned policies can be found on our project website.
                </blockquote>
            </div>
            <div class="pubjournal">Conference on Robot Learning (CoRL), 2020
            <div style="font-size:small">
                <a href="https://sites.google.com/view/softgym/home">[Project Page]</a>
                <a href="https://github.com/Xingyu-Lin/softgym">[Code]</a>
                <a href="javascript:copy(div2020softgym, bib2020softgym)">[Bibtex]</a>
                <a href="javascript:copy(div2020softgym, abs2020softgym)">[Abstract]</a>
                <a href="https://arxiv.org/pdf/2011.07215.pdf">[PDF]</a>
            </div>
            <div id="div2020softgym" class="pubInfo"></div>
            </div>
            <br>
        </td>
    </tr>

    <tr>
        <td class="pubimg" width="250" height="100">
            <img src="../pics/corl2020_ROLL.jpg" img width="250">
        </td>
        <td><a href="https://arxiv.org/abs/2011.06777">Visual Self-Supervised Reinforcement Learning with Object Reasoning</a><br>
            <div class="pubauthor">
                Yufei Wang*, Gautham Narayan Narasimhan*, Xingyu Lin, Brian Okorn, David Held<br>
            </div>
            <div id="bib2020roll" style="display:none">
                    <blockquote>
<pre>@inproceedings{corl2020roll,
title={ROLL: Visual Self-Supervised Reinforcement Learning with Object Reasoning},
author={Wang, Yufei and Narasimhan Gautham and Lin, Xingyu and Okorn, Brian and Held, David},
booktitle={Conference on Robot Learning},
year={2020}
}</pre>
                </blockquote>
            </div>
            <div id="abs2020roll" style="display:none">
                <blockquote>
                     Current image-based reinforcement learning (RL) algorithms typically operate on the whole image without performing object-level reasoning.  This leads to inefficient goal sampling and ineffective reward functions. In this paper, we improve upon previous visual self-supervised RL by incorporating object-level reasoning and occlusion reasoning. Specifically, we use unknown object segmentation to ignore distractors in the scene for better reward computation and goal generation; we further enable occlusion reasoning by employing a novel auxiliary loss and training scheme. We demonstrate that our proposed algorithm,   ROLL (Reinforcement learning with Object Level Learning), learns dramatically faster and achieves better final performance compared with previous methods in several simulated visual control tasks. Project video and code
                     are available at https://sites.google.com/andrew.cmu.edu/roll.
                </blockquote>
            </div>
            <div class="pubjournal">Conference on Robot Learning (CoRL), 2020
            <div style="font-size:small">
                <a href="https://sites.google.com/andrew.cmu.edu/roll/home">[Project Page]</a>
                <a href="https://github.com/yufeiwang63/ROLL">[Code]</a>
                <a href="javascript:copy(div2020roll, bib2020roll)">[Bibtex]</a>
                <a href="javascript:copy(div2020roll, abs2020roll)">[Abstract]</a>
                <a href="https://arxiv.org/pdf/2011.06777.pdf">[PDF]</a>
            </div>
            <div id="div2020roll" class="pubInfo"></div>

            </div>
            <br>
        </td>
    </tr>

    <tr>
        <td class="pubimg" width="250" height="100">
            <img src="../pics/corl2020_plas.png" img width="250">
        </td>
        <td><a href="https://arxiv.org/abs/2011.07213">Latent Action Space for Offline Reinforcement Learning</a><br>
            <div class="pubauthor">
                Wenxuan Zhou, Sujay Bajracharya, David Held<br>
            </div>
            <div class="pubjournal">Conference on Robot Learning (CoRL), 2020 - <award>Plenary talk</award> (Selection rate 4.1%)
             <div id="bib2020corl" style="display:none">
                <blockquote>
                    <pre>@inproceedings{PLAS_corl2020,
 title={PLAS: Latent Action Space for Offline Reinforcement Learning},
 author={Zhou, Wenxuan and Bajracharya, Sujay and Held, David},
 booktitle={Conference on Robot Learning},
 year={2020}
 }</pre>
                </blockquote>
            </div>
            <div id="abs2020corl" style="display:none">
                <blockquote>
The goal of offline reinforcement learning is to learn a policy from a fixed dataset, without further interactions with the environment.  This setting will be an increasingly more important paradigm for real-world applications of reinforcement learning such as robotics, in which data collection is slow and potentially dangerous. Existing off-policy algorithms have limited performance on static datasets due to extrapolation errors from out-of-distribution actions. This leads to the challenge of constraining the policy to select actions within the support of the dataset during training. We propose to simply learn the Policy in the Latent Action Space (PLAS) such that this requirement is naturally satisfied. We evaluate our method on continuous control benchmarks in simulation and a deformable object manipulation task with a physical robot. We demonstrate that our method provides competitive performance consistently across various continuous control tasks and different types of datasets, outperforming existing offline reinforcement learning methods with explicit constraints.                </blockquote>
            </div>
            <div style="font-size:small">
                <a href="https://sites.google.com/view/latent-policy">[Project Page]</a>
                <a href="https://github.com/Wenxuan-Zhou/PLAS">[Code]</a>
                <a href="javascript:copy(div2020corl, bib2020corl)">[Bibtex]</a>
                <a href="javascript:copy(div2020corl, abs2020corl)">[Abstract]</a>
                <a href="https://arxiv.org/pdf/2011.07213.pdf">[PDF]</a>
            </div>
            <div id="div2020corl" class="pubInfo"></div>
            </div>
            <br>
        </td>
    </tr>

    <tr>
        <td class="pubimg" width="250" height="100">
            <img src="../pics/panonet3db.jpg" img width="250" height="100">
        </td>
        <td><a href="https://arxiv.org/pdf/2012.09418.pdf">PanoNet3D: Combining Semantic and Geometric Understanding for LiDARPoint Cloud Detection</a><br>
            <div class="pubauthor">
                Xia Chen, Jianren Wang, David Held, Martial Hebert<br>
            </div>
            <div id="bib20203dv" style="display:none">
                    <blockquote>
<pre>@inproceedings{xia20panonet3d,
    author = "Chen, Xia 
    and Wang, Jianren 
    and Held, David 
    and Hebert, Martial",
    title = "PanoNet3D: Combining Semantic and Geometric Understanding for LiDARPoint Cloud Detection",
    booktitle = "3DV",
    year = "2020"
}</pre>
                    </blockquote>
            </div>
            <div id="abs20203dv" style="display:none">
                <blockquote>
                    Visual data in autonomous driving perception, such as camera image and LiDAR point cloud, can be interpreted as a mixture of two aspects: semantic feature and geometric structure. Semantics come from the appearance and context of objects to the sensor, while geometric structure is the actual 3D shape of point clouds. Most detectors on LiDAR point clouds focus only on analyzing the geometric structure of objects in real 3D space. Unlike previous works, we propose to learn both semantic feature and geometric structure via a unified multi-view framework. Our method exploits the nature of LiDAR scans -- 2D range images, and applies well-studied 2D convolutions to extract semantic features. By fusing semantic and geometric features, our method outperforms state-of-the-art approaches in all categories by a large margin. The methodology of combining semantic and geometric features provides a unique perspective of looking at the problems in real-world 3D point cloud detection.
                </blockquote>
            </div>
            <div class="pubjournal">International Conference on 3D Vision (3DV), 2020
            <div style="font-size:small">
                <a href="https://jianrenw.github.io/PanoNet3D/">[Project Page]</a>
                <a href="https://github.com/stooloveu/Det3D">[Code]</a>
                <a href="javascript:copy(div20203dv, bib20203dv)">[Bibtex]</a>
                <a href="javascript:copy(div20203dv, abs20203dv)">[Abstract]</a>
                <a href="https://arxiv.org/pdf/2012.09418.pdf">[PDF]</a>
            </div>
            <div id="div20203dv" class="pubInfo"></div>
            </div>
            <br>
        </td>
    </tr>

    <tr>
        <td class="pubimg" width="250" height="100">
            <img src="../pics/eccv2020lightcurtains.jpg" img width="250">
        </td>
        <td><a href="https://arxiv.org/abs/2008.02191">Active Perception using Light Curtains for Autonomous Driving</a><br>
            <div class="pubauthor">
                Siddharth Ancha, Yaadhav Raaj, Peiyun Hu, Srinivasa Narasimhan, David Held<br>
            </div>
            <div id="bib2020eccv" style="display:none">
                    <blockquote>
<pre>@InProceedings{Ancha_2020_ECCV,
  author="Ancha, Siddharth
  and Raaj, Yaadhav
  and Hu, Peiyun
  and Narasimhan, Srinivasa G.
  and Held, David",
  editor="Vedaldi, Andrea
  and Bischof, Horst
  and Brox, Thomas
  and Frahm, Jan-Michael",
  title="Active Perception Using Light Curtains for Autonomous Driving",
  booktitle="Computer Vision -- ECCV 2020",
  year="2020",
  publisher="Springer International Publishing",
  address="Cham",
  pages="751--766",
  isbn="978-3-030-58558-7"
}</pre>
                </blockquote>
            </div>
            <div id="abs2020eccv" style="display:none">
                <blockquote>
                    Most real-world 3D sensors such as LiDARs perform fixed scans of the entire environment, while being decoupled from the recognition system that processes the sensor data. In this work, we propose a method for 3D object recognition using light curtains, a resource-efficient controllable sensor that measures depth at user-specified locations in the environment. Crucially, we propose using prediction uncertainty of a deep learning based 3D point cloud detector to guide active perception. Given a neural network’s uncertainty, we derive an optimization objective to place light curtains using the principle of maximizing information gain. Then, we develop a novel and efficient optimization algorithm to maximize this objective by encoding the physical constraints of the device into a constraint graph and optimizing with dynamic programming. We show how a 3D detector can be trained to detect objects in a scene by sequentially placing uncertainty-guided light curtains to successively improve detection accuracy.
                </blockquote>
            </div>
            <div class="pubjournal">European Conference on Computer Vision (ECCV), 2020 - <award>Spotlight</award> (Selection rate 5.3%)
            <div style="font-size:small">
                <a href="http://siddancha.github.io/projects/active-perception-light-curtains/">[Project Page]</a>
                <a href="https://github.com/siddancha/active-perception-light-curtains">[Code]</a>
                <a href="javascript:copy(div2020eccv, bib2020eccv)">[Bibtex]</a>
                <a href="javascript:copy(div2020eccv, abs2020eccv)">[Abstract]</a>
                <a href="https://arxiv.org/pdf/2008.02191.pdf">[PDF]</a>
                <!-- <a href="GOTURN/supplement.pdf">[Supplement]</a> -->
            </div>
            <div id="div2020eccv" class="pubInfo"></div>
            
            </div>
            <br>
        </td>
    </tr>
    <tr>
        <td class="pubimg" width="250" height="100">
            <img src="../pics/iros2020_website_thumbnail.png" img width="250">
        </td>
        <td><a href="https://arxiv.org/abs/2008.05626">Cloth Region Segmentation for Robust Grasp Selection</a><br>
            <div class="pubauthor">
                Jianing Qian*, Thomas Weng*, Luxin Zhang, Brian Okorn, David Held<br>
            </div>
            <div class="pubjournal">International Conference on Intelligent Robots and Systems (IROS), 2020
            </div>
            <div id="bibqian2020iros" style="display:none">
                <blockquote>
                    <pre>
@InProceedings{Qian_2020_IROS,
    author="Qian, Jianing
    and Weng, Thomas
    and Zhang, Luxin
    and Okorn, Brian
    and Held, David",
    title="Cloth Region Segmentation for Robust Grasp Selection",
    booktitle="International Conference on Intelligent Robots and Systems",
    year="2020",
    publisher="IEEE"}
                    </pre>
                </blockquote>
            </div>
            <div id="absqian2020iros" style="display:none">
                <blockquote>
                    Cloth detection and manipulation is a common task in domestic and industrial settings, yet such tasks remain a challenge for robots due to cloth deformability. Furthermore, in many cloth-related tasks like laundry folding and bed making, it is crucial to manipulate specific regions like edges and corners, as opposed to folds. In this work, we focus on the problem of segmenting and grasping these key regions. Our approach trains a network to segment the edges and corners of a cloth from a depth image, distinguishing such regions from wrinkles or folds. We also provide a novel algorithm for estimating the grasp location, direction, and directional uncertainty from the segmentation. We demonstrate our method on a real robot system and show that it outperforms baseline methods on grasping success. Video and other supplementary materials are available at: <a href="https://sites.google.com/view/cloth-segmentation">this https URL</a>.
                </blockquote>
            </div>
            <div style="font-size:small">
                <a href="https://sites.google.com/view/cloth-segmentation">[Project Page]</a>
                <!-- <a href="">[Code]</a> -->
                <a href="javascript:copy(divqian2020iros, bibqian2020iros)">[Bibtex]</a>
                <a href="javascript:copy(divqian2020iros, absqian2020iros)">[Abstract]</a>
                <a href="https://arxiv.org/pdf/2008.05626.pdf">[PDF]</a>
            </div>
            <div id="divqian2020iros" class="pubInfo"></div>
            <br>
        </td>
    </tr>
    <tr>
        <td class="pubimg" width="250" height="100">
            <img src="../pics/jianreniros2020.jpg" img width="250">
        </td>
        <td><a href="https://arxiv.org/abs/2008.08173">Uncertainty-aware Self-supervised 3D Data Association</a><br>
            <div class="pubauthor">
                Jianren Wang, Siddharth Ancha, Yi-Ting Chen, David Held<br>
            </div>
            <div id="bibjianren2020iros" style="display:none">
                    <blockquote>
<pre>@inproceedings{jianren20s3da,
    author = "Wang, Jianren 
    and Ancha, Siddharth 
    and Chen, Yi-Ting 
    and Held, David",
    title = "Uncertainty-aware Self-supervised 3D Data Association",
    booktitle = "IROS",
    year = "2020"
}</pre>
                    </blockquote>
            </div>
            <div id="absjianren2020iros" style="display:none">
                <blockquote>
                    3D object trackers usually require training on large amounts of annotated data that is expensive and time-consuming to collect. Instead, we propose leveraging vast unlabeled datasets by self-supervised metric learning of 3D object trackers, with a focus on data association. Large scale annotations for unlabeled data are cheaply obtained by automatic object detection and association across frames. We show how these self-supervised annotations can be used in a principled manner to learn point-cloud embeddings that are effective for 3D tracking. We estimate and incorporate uncertainty in self-supervised tracking to learn more robust embeddings, without needing any labeled data. We design embeddings to differentiate objects across frames, and learn them using uncertainty-aware self-supervised training. Finally, we demonstrate their ability to perform accurate data association across frames, towards effective and accurate 3D tracking.
                </blockquote>
            </div>
            <div class="pubjournal">International Conference on Intelligent Robots and Systems (IROS), 2020
            <div style="font-size:small">
                <a href="https://jianrenw.github.io/Self-Supervised-3D-Data-Association/">[Project Page]</a>
                <a href="https://github.com/jianrenw/Self-Supervised-3D-Data-Association">[Code]</a>
                <a href="javascript:copy(divjianren2020iros, bibjianren2020iros)">[Bibtex]</a>
                <a href="javascript:copy(divjianren2020iros, absjianren2020iros)">[Abstract]</a>
                <a href="https://arxiv.org/pdf/2008.08173v1.pdf">[PDF]</a>
            </div>
            <div id="divjianren2020iros" class="pubInfo"></div>
            </div>
            <br>
        </td>
    </tr>
    <tr>
        <td class="pubimg" width="250" height="100">
            <img src="../pics/LearningOrientationDistributions-Website.png" img width="250">
        </td>
        <td><a href="https://arxiv.org/abs/2007.01418">Learning Orientation Distributions for Object Pose Estimation</a><br>
            <div class="pubauthor">
                Brian Okorn, Mengyun Xu, Martial Hebert, David Held<br>
            </div>
            <div class="pubjournal">International Conference on Intelligent Robots and Systems (IROS), 2020
            <!--div style="font-size:small">
                <a href="GOTURN/GOTURN.html">[Project Page]</a>
                <a href="GOTURN/GOTURN.pdf">[Full Paper]</a>
                <a href="GOTURN/supplement.pdf">[Supplement]</a></div-->
            </div>
            <br>
        </td>
    </tr>
    <tr>
        <td class="pubimg" width="250" height="100">
            <img src="../pics/ab3dmot.jpg" img width="250">
        </td>
        <td><a href="https://arxiv.org/abs/1907.03961">3D Multi-Object Tracking: A Baseline and New Evaluation Metrics</a><br>
            <div class="pubauthor">
                Xinshuo Weng, Jianren Wang, David Held, Kris Kitani<br>
            </div>
            <div id="bibxinshuo2020iros" style="display:none">
                    <blockquote>
<pre>@article{Weng2020_AB3DMOT, 
author = {Weng, Xinshuo and Wang, Jianren and Held, David and Kitani, Kris}, 
journal = {IROS}, 
title = {{3D Multi-Object Tracking: A Baseline and New Evaluation Metrics}}, 
year = {2020} 
}</pre>
                    </blockquote>
            </div>
            <div id="absxinshuo2020iros" style="display:none">
                <blockquote>
                    3D multi-object tracking (MOT) is an essential component for many applications such as autonomous driving and assistive robotics. Recent work on 3D MOT focuses on developing accurate systems giving less attention to practical considerations such as computational cost and system complexity. In contrast, this work proposes a simple real-time 3D MOT system. Our system first obtains 3D detections from a LiDAR point cloud. Then, a straightforward combination of a 3D Kalman filter and the Hungarian algorithm is used for state estimation and data association. Additionally, 3D MOT datasets such as KITTI evaluate MOT methods in the 2D space and standardized 3D MOT evaluation tools are missing for a fair comparison of 3D MOT methods. Therefore, we propose a new 3D MOT evaluation tool along with three new metrics to comprehensively evaluate 3D MOT methods. We show that, although our system employs a combination of classical MOT modules, we achieve state-of-the-art 3D MOT performance on two 3D MOT benchmarks (KITTI and nuScenes). Surprisingly, although our system does not use any 2D data as inputs, we achieve competitive performance on the KITTI 2D MOT leaderboard. Our proposed system runs at a rate of 207.4 FPS on the KITTI dataset, achieving the fastest speed among all modern MOT systems.
                </blockquote>
            </div>
            <div class="pubjournal">International Conference on Intelligent Robots and Systems (IROS), 2020
            <div style="font-size:small">
                <a href="http://www.xinshuoweng.com/projects/AB3DMOT/">[Project Page]</a>
                <a href="https://github.com/xinshuoweng/AB3DMOT">[Code]</a>
                <a href="javascript:copy(divxinshuo2020iros, bibxinshuo2020iros)">[Bibtex]</a>
                <a href="javascript:copy(divxinshuo2020iros, absxinshuo2020iros)">[Abstract]</a>
                <a href="http://www.xinshuoweng.com/projects/AB3DMOT/">[PDF]</a>
            </div>
            <div id="divxinshuo2020iros" class="pubInfo"></div>
            </div>
            <br>
        </td>
    </tr>
    <tr>
        <td class="pubimg" width="250" height="100">
            <img src="../pics/jgwtf/Slide1.png" img width="250">
        </td>
        <td><a href="https://arxiv.org/abs/1912.00497">Just Go with the Flow: Self-Supervised Scene Flow Estimation</a><br>
            <div class="pubauthor">
                Himangi Mittal, Brian Okorn, David Held<br>
            </div>
            <div id="bib2020cvprflow" style="display:none">
                    <blockquote>
<pre>
@InProceedings{Mittal_2020_CVPR,
author = {Mittal, Himangi and Okorn, Brian and Held, David},
title = {Just Go With the Flow: Self-Supervised Scene Flow Estimation},
booktitle = {Proceedings of the IEEE/CVF Conference on Computer Vision and Pattern Recognition (CVPR)},
month = {June},
year = {2020}
} 
</pre>
                </blockquote>
            </div>
            <div id="abs2020cvprflow" style="display:none">
                <blockquote>
                     When interacting with highly dynamic environments, scene flow allows autonomous systems to reason about the non-rigid motion of multiple independent objects. This is of particular interest in the field of autonomous driving, in which many cars, people, bicycles, and other objects need to be accurately tracked. Current state-of-the-art methods require annotated scene flow data from autonomous driving scenes to train scene flow networks with supervised learning. As an alternative, we present a method of training scene flow that uses two self-supervised losses, based on nearest neighbors and cycle consistency. These self-supervised losses allow us to train our method on large unlabeled autonomous driving datasets; the resulting method matches current state-of-the-art supervised performance using no real world annotations and exceeds state-of-the-art performance when combining our self-supervised approach with supervised learning on a smaller labeled dataset.
                </blockquote>
            </div>
            <div class="pubjournal">Conference on Computer Vision and Pattern Recognition (CVPR), 2020 - <award>Oral</award> (Selection rate 5.7%)
            <div style="font-size:small">
                <a href="https://just-go-with-the-flow.github.io/">[Project Page]</a>
                <a href="https://github.com/HimangiM/Just-Go-with-the-Flow-Self-Supervised-Scene-Flow-Estimation">[Code]</a>
                <a href="javascript:copy(div2020cvprflow, bib2020cvprflow)">[Bibtex]</a>
                <a href="javascript:copy(div2020cvprflow, abs2020cvprflow)">[Abstract]</a>
                <a href="https://arxiv.org/pdf/1912.00497.pdf">[PDF]</a>
                <!-- <a href="GOTURN/supplement.pdf">[Supplement]</a> -->
            </div>
            <!--div style="font-size:small">
                <a href="GOTURN/GOTURN.html">[Project Page]</a>
                <a href="GOTURN/GOTURN.pdf">[Full Paper]</a>
                <a href="GOTURN/supplement.pdf">[Supplement]</a></div-->
                <div id="div2020cvprflow" class="pubInfo"></div>
            </div>
            <br>
        </td>
    </tr>
    <tr>
        <td class="pubimg" width="250" height="100">
            <img src="../pics/peiyuncvpr2020/splash2.jpg" img width="250" height="100">
        </td>
        <td><a href="https://arxiv.org/abs/1912.04986">What You See is What You Get: Exploiting Visibility for 3D Object Detection</a><br>
            <div class="pubauthor">
                Peiyun Hu, Jason Ziglar, David Held, Deva Ramanan<br>
            </div>
            <div class="pubjournal">Conference on Computer Vision and Pattern Recognition (CVPR), 2020 - <award>Oral</award> (Selection rate 5.7%)</div>
            <!--div style="font-size:small">
                <a href="GOTURN/GOTURN.html">[Project Page]</a>
                <a href="GOTURN/GOTURN.pdf">[Full Paper]</a>
                <a href="GOTURN/supplement.pdf">[Supplement]</a></div-->
            <br>
        </td>
    </tr>
    <tr>
        <td class="pubimg" width="250" height="100">
            <img src="../pics/t3_cropped.png" img width="250">
        </td>
        <td><a href="https://arxiv.org/abs/2006.00028">Multi-Modal Transfer Learning for Grasping Transparent and Specular Objects</a><br>
            <div class="pubauthor">
                Thomas Weng, Amith Pallankize, Yimin Tang, Oliver Kroemer, David Held<br>
            </div>
            <div class="pubjournal">Robotics and Automation Letters (RA-L) with presentation at the International Conference of Robotics and Automation (ICRA), 2020</div>
            <div id="bibweng2020ral" style="display:none">
                <blockquote>
                    <pre>
@ARTICLE{9001238,
    author={Thomas Weng and Amith Pallankize and Yimin Tang and Oliver Kroemer and David Held},
    journal={IEEE Robotics and Automation Letters}, 
    title={Multi-Modal Transfer Learning for Grasping Transparent and Specular Objects}, 
    year={2020},
    volume={5},
    number={3},
    pages={3791-3798},
    doi={10.1109/LRA.2020.2974686}}
                    </pre>
                </blockquote>
            </div>
            <div id="absweng2020ral" style="display:none">
                <blockquote>
                    State-of-the-art object grasping methods rely on depth sensing to plan robust grasps, but commercially available depth sensors fail to detect transparent and specular objects. To improve grasping performance on such objects, we introduce a method for learning a multi-modal perception model by bootstrapping from an existing uni-modal model. This transfer learning approach requires only a pre-existing uni-modal grasping model and paired multi-modal image data for training, foregoing the need for ground-truth grasp success labels nor real grasp attempts. Our experiments demonstrate that our approach is able to reliably grasp transparent and reflective objects. Video and supplementary material are available at <a href="https://sites.google.com/view/transparent-specular-grasping">https://sites.google.com/view/transparent-specular-grasping</a>.
                </blockquote>
            </div>
            <div style="font-size:small">
                <a href="https://sites.google.com/view/transparent-specular-grasping">[Project Page]</a>
                <!-- <a href="">[Code]</a> -->
                <a href="javascript:copy(divweng2020ral, bibweng2020ral)">[Bibtex]</a>
                <a href="javascript:copy(divweng2020ral, absweng2020ral)">[Abstract]</a>
                <a href="https://arxiv.org/pdf/2006.00028.pdf">[PDF]</a>
            </div>
            <div id="divweng2020ral" class="pubInfo"></div>
            <br>
        </td>
    </tr>
    <tr>
        <td class="pubimg" width="250" height="100">
            <img src="../pics/peiyunral2020/output.jpg" img width="250">
        </td>
        <td><a href="https://arxiv.org/abs/1912.04976">Learning to Optimally Segment Point Clouds</a><br>
            <div class="pubauthor">
                Peiyun Hu, David Held*, Deva Ramanan*<br>
            </div>
            <div class="pubjournal">Robotics and Automation Letters (RA-L) with presentation at the International Conference of Robotics and Automation (ICRA), 2020</div>
            <!--div style="font-size:small">
                <a href="GOTURN/GOTURN.html">[Project Page]</a>
                <a href="GOTURN/GOTURN.pdf">[Full Paper]</a>
                <a href="GOTURN/supplement.pdf">[Supplement]</a></div-->
            <br>
        </td>
    </tr>
    <!-- <tr class="year"><td><li class="year">2019</li></td></tr> -->
    <tr>
        <td class="pubimg">
            <img src="../pics/CoRL2019.png" width="250">
        </td>
        <td><a href="https://arxiv.org/abs/1912.12270">Combining Deep Learning and Verification for Precise Object Instance Detection</a><br>
            <div class="pubauthor">
                Siddharth Ancha*, Junyu Nan*, David Held</div>
            <div id="bib2019corl" style="display:none">
                    <blockquote>
<pre>@inproceedings{FlowVerify2019CoRL,
  author    = {Siddharth Ancha and
               Junyu Nan and
               David Held},
  editor    = {Leslie Pack Kaelbling and
               Danica Kragic and
               Komei Sugiura},
  title     = {Combining Deep Learning and Verification for Precise Object Instance
               Detection},
  booktitle = {3rd Annual Conference on Robot Learning, CoRL 2019, Osaka, Japan,
               October 30 - November 1, 2019, Proceedings},
  series    = {Proceedings of Machine Learning Research},
  volume    = {100},
  pages     = {122--141},
  publisher = {{PMLR}},
  year      = {2019},
  url       = {http://proceedings.mlr.press/v100/ancha20a.html},
  timestamp = {Mon, 25 May 2020 15:01:26 +0200},
  biburl    = {https://dblp.org/rec/conf/corl/AnchaNH19.bib},
  bibsource = {dblp computer science bibliography, https://dblp.org}
}</pre>
                </blockquote>
            </div>
            <div id="abs2019corl" style="display:none">
                <blockquote>
                    Deep learning object detectors often return false positives with very high confidence. Although they optimize generic detection performance, such as mean average precision (mAP), they are not designed for reliability. For a reliable detection system, if a high confidence detection is made, we would want high certainty that the object has indeed been detected. To achieve this, we have developed a set of verification tests which a proposed detection must pass to be accepted. We develop a theoretical framework which proves that, under certain assumptions, our verification tests will not accept any false positives. Based on an approximation to this framework, we present a practical detection system that can verify, with high precision, whether each detection of a machine-learning based object detector is correct. We show that these tests can improve the overall accuracy of a base detector and that accepted examples are highly likely to be correct. This allows the detector to operate in a high precision regime and can thus be used for robotic perception systems as a reliable instance detection method.
                </blockquote>
            </div>
            <div class="pubjournal">Conference on Robot Learning (CoRL), 2019
            <div style="font-size:small">
                <a href="https://jnan1.github.io/FlowVerify/">[Project Page]</a>
                <a href="https://github.com/siddancha/FlowVerify">[Code]</a>
                <a href="javascript:copy(div2019corl, bib2019corl)">[Bibtex]</a>
                <a href="javascript:copy(div2019corl, abs2019corl)">[Abstract]</a>
                <a href="https://arxiv.org/pdf/1912.12270.pdf">[PDF]</a>
                <!-- <a href="GOTURN/supplement.pdf">[Supplement]</a> -->
            </div>
            <div id="div2019corl" class="pubInfo"></div>
            
            </div>
            <br>
        </td>
    </tr>
    <tr>
        <td class="pubimg">
            <img src="../pics/2019_olaux.png" width="250" height="100">
        </td>
        <td><a href="https://papers.nips.cc/paper/8724-adaptive-auxiliary-task-weighting-for-reinforcement-learning">Adaptive Auxiliary Task Weighting for Reinforcement Learning</a><br>
            <div class="pubauthor">
                Xingyu Lin*, Harjatin Baweja*, George Kantor, David Held</div>
            <div class="pubjournal">Neural Information Processing Systems (NeurIPS), 2019</div>
            <!--div style="font-size:small">
                <a href="GOTURN/GOTURN.html">[Project Page]</a>
                <a href="GOTURN/GOTURN.pdf">[Full Paper]</a>
                <a href="GOTURN/supplement.pdf">[Supplement]</a></div-->
            <br>
        </td>
    </tr>
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/icra19.png" width="250" height="100">
        </td>
        <td><a href="https://arxiv.org/abs/1903.06309">Adaptive Variance for Changing Sparse-Reward Environments</a><br>
            <div class="pubauthor">
                Xingyu Lin, Pengsheng Guo, Carlos Florensa, David Held</div>
            <div class="pubjournal">International Conference of Robotics and Automation (ICRA), 2019</div>
            <!--div style="font-size:small">
                <a href="GOTURN/GOTURN.html">[Project Page]</a>
                <a href="GOTURN/GOTURN.pdf">[Full Paper]</a>
                <a href="GOTURN/supplement.pdf">[Supplement]</a></div-->
            <br>
        </td>
    </tr>
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/pcn.png" width="250" height="100">
        </td>
        <td><a href="http://arxiv.org/abs/1808.00671">PCN: Point Completion Network - <award>Best Paper Honorable Mention</award></a><br>
            <div class="pubauthor">
                Wentao Yuan, Tejas Khot, David Held, Christoph Mertz, Martial Hebert</div>
            <div class="pubjournal">International Conference on 3D Vision (3DV), 2018</div>
            <!--div style="font-size:small">
                <a href="GOTURN/GOTURN.html">[Project Page]</a>
                <a href="GOTURN/GOTURN.pdf">[Full Paper]</a>
                <a href="GOTURN/supplement.pdf">[Supplement]</a></div-->
            <br>
        </td>
    </tr>
    <!-- <tr class="year"><td><li class="year">2018</li></td></tr> -->
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/ant-maze.png" width="250" height="100">
        </td>
        <td><a href="https://arxiv.org/abs/1705.06366">Automatic Goal Generation for Reinforcement Learning Agents</a><br>
            <div class="pubauthor">
                Carlos Florensa*, David Held*, Xinyang Geng*, Pieter Abbeel</div>
            <div class="pubjournal">International Conference on Machine Learning (ICML), 2018</div>
            <!--div style="font-size:small">
                <a href="GOTURN/GOTURN.html">[Project Page]</a>
                <a href="GOTURN/GOTURN.pdf">[Full Paper]</a>
                <a href="GOTURN/supplement.pdf">[Supplement]</a></div-->
            <br>
        </td>
    </tr>
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/enabling_robots_RSS_2017.png" width="250">
        </td>
        <td><a href="https://rdcu.be/ZM50">Enabling Robots to Communicate their Objectives</a><br>
            <div class="pubauthor">
                Sandy Han Huang, David Held, Pieter Abbeel, Anca D. Dragan</div>
            <div class="pubjournal">Autonomous Robotics (AURO), 2018</div>
            <!--div style="font-size:small">
                <a href="GOTURN/GOTURN.html">[Project Page]</a>
                <a href="GOTURN/GOTURN.pdf">[Full Paper]</a>
                <a href="GOTURN/supplement.pdf">[Supplement]</a></div-->
            <br>
        </td>
    </tr>
    <!-- <tr class="year"><td><li class="year">2017</li></td></tr> -->
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/reverse_curr2.png" width="250" height="100">
        </td>
        <td><a href="https://arxiv.org/abs/1707.05300">Reverse Curriculum Generation for Reinforcement Learning</a><br>
            <div class="pubauthor">Carlos Florensa, David Held, Markus Wulfmeier, Pieter Abbeel</div>
            <div class="pubjournal">Conference on Robot Learning (CoRL), 2017</div>
            <!--div style="font-size:small">
                <a href="GOTURN/GOTURN.html">[Project Page]</a>
                <a href="GOTURN/GOTURN.pdf">[Full Paper]</a>
                <a href="GOTURN/supplement.pdf">[Supplement]</a></div-->
            <br>
        </td>
    </tr>
    <!--IROS 2017-->
    <tr>
        <td>
            <img src="../DavidHeld_files/transfer.png" width="250">
        </td>
        <td><a href="DavidHeld_files/IROS___RL_pushing.pdf">Policy  Transfer via Modularity</a><br>
            <div class="pubauthor">
                Ignasi Clavera*, David Held*, Pieter Abbeel</div>
            <div class="pubjournal">International Conference on Intelligent Robots and Systems (IROS), 2017</div>
            <!--div style="font-size:small">
                <a href="GOTURN/GOTURN.html">[Project Page]</a>
                <a href="GOTURN/GOTURN.pdf">[Full Paper]</a>
                <a href="GOTURN/supplement.pdf">[Supplement]</a></div-->
            <br>
        </td>
    </tr>
    <!--ICML 2017-->
    <tr>
        <td>
            <img src="../DavidHeld_files/humanoid.png" width="250">
        </td>
        <td><a href="https://arxiv.org/abs/1705.10528">Constrained Policy Optimization</a><br>
            <div class="pubauthor">
                Joshua Achiam, David Held, Aviv Tamar, Pieter Abbeel</div>
            <div class="pubjournal">International Conference on Machine Learning (ICML), 2017</div>
            <!--div style="font-size:small">
                <a href="GOTURN/GOTURN.html">[Project Page]</a>
                <a href="GOTURN/GOTURN.pdf">[Full Paper]</a>
                <a href="GOTURN/supplement.pdf">[Supplement]</a></div-->
            <br>
        </td>
    </tr>
    <!--RSS 2017-->
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/enabling_robots_RSS_2017.png" width="250">
        </td>
        <td><a href="https://arxiv.org/abs/1702.03465">Enabling Robots to Communicate their Objectives</a><br>
            <div class="pubauthor">
                Sandy H. Huang, David Held, Pieter Abbeel, Anca D. Dragan</div>
            <div class="pubjournal">Robotics: Science and Systems (RSS), 2017</div>
            <!--div style="font-size:small">
                <a href="GOTURN/GOTURN.html">[Project Page]</a>
                <a href="GOTURN/GOTURN.pdf">[Full Paper]</a>
                <a href="GOTURN/supplement.pdf">[Supplement]</a></div-->
            <br>
        </td>
    </tr>
    <!--ICRA 2017-->
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/safe_transfer3.png" width="250">
        </td>
        <td><a href="https://arxiv.org/abs/1705.05394">Probabilistically Safe Policy Transfer</a><br>
            <div class="pubauthor">
                David Held, Zoe McCarthy, Michael Zhang, Fred Shentu, Pieter Abbeel</div>
            <div class="pubjournal">International Conference on Robotics and Automation (ICRA), 2017</div>
            <!--div style="font-size:small">
                <a href="GOTURN/GOTURN.html">[Project Page]</a>
                <a href="GOTURN/GOTURN.pdf">[Full Paper]</a>
                <a href="GOTURN/supplement.pdf">[Supplement]</a></div-->
            <br>
        </td>
    </tr>
    <!--tr><td><li class="year"> 2016</li></td></tr-->
    <!--ul-->
    <!-- ------------------------------------------------------------------------
        2016
        --------------------------------------------------------------------- -->
    <!--li class="pubitem"-->
    <!--table border="0" cellpadding="0" cellspacing="0" cellpadding="100" width="800" bgcolor="#FFFFFF"-->
    <!-- <tr class="year"><td><li class="year">2016</li></td></tr> -->
    <!--ECCV 2016-->
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/pull7f-web_d.png" width="250">
                </td>
        <td><a href="GOTURN/GOTURN.pdf">Learning to Track at 100 FPS with Deep Regression Networks</a><br>
            <div class="pubauthor">David Held, Sebastian Thrun, Silvio Savarese</div>
            <div class="pubjournal">European Conference on Computer Vision (ECCV), 2016</div>
            <div style="font-size:small">
                <a href="GOTURN/GOTURN.html">[Project Page]</a>
                <a href="GOTURN/GOTURN.pdf">[Full Paper]</a>
                <a href="GOTURN/supplement.pdf">[Supplement]</a></div>
            <br>
        </td>
    </tr>
    <!--RSS 2016-->
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/pull_fig2.png" width="250">
                </td>
        <td><a href="segmentation3D/segmentation3D.html">A Probabilistic Framework for Real-time 3D Segmentation using Spatial, Temporal, and Semantic Cues</a><br>
            <div class="pubauthor">David Held, Devin Guillory, Brice Rebsamen, Sebastian Thrun, Silvio Savarese</div>
            <div class="pubjournal">Robotics: Science and Systems (RSS), 2016</div>
            <a href="segmentation3D/segmentation3D.html"><div style="font-size:small">[Project Page]</div></a><br>
        </td>
    </tr>
    <!--ICRA 2016-->
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/pull6_flatb.png" width="250">
                </td>
        <td><a href="http://arxiv.org/abs/1507.08286">Robust Single-View Instance Recognition</a><br>
            <div class="pubauthor">David Held, Sebastian Thrun, Silvio Savarese</div>
            <div class="pubjournal">International Conference on Robotics and Automation (ICRA), 2016</div>
            <!--a href="http://arxiv.org/abs/1507.08286">Arxiv version</a-->
        </td>
    </tr>
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/tracker_comparison3.png" height="120">
        </td>
        <td>
            <a href="DavidHeld_files/ijrr_tracking.pdf">Robust Real-Time Tracking Combining 3D Shape, Color, and Motion </a><br>
            <div class="pubauthor">David Held, Jesse Levinson, Sebastian Thrun, Silvio Savarese</div>
            <div class="pubjournal">International Journal of Robotics Research (IJRR), 2016</div>
            <div class="pubspan"><a href="anytime_tracking.html">[Project Page]</a></div><br>
            <!--a href="DavidHeld_files/ijrr_tracking.pdf">[Full paper]</a-->
        </td>
    </tr>
    <!--tr><td><li class="year"> 2015 </li></td></tr-->
    <!-- <tr class="year"><td><li class="year">2014</li></td></tr> -->
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/Pull3.png" height="120">
        </td>
        <td class="pubitem">
            <div class="pubitem">
                <a class="pubtitle" href="papers/rss14_tracking.pdf">
                    Combining 3D Shape, Color, and Motion for Robust Anytime Tracking</a>
                <div>
                    <a class="pubauthor" href="http://stanford.edu/~davheld">David Held</a>,
                    <a class="pubauthor">Jesse Levinson</a>,
                    <a class="pubauthor" href="http://robots.stanford.edu/">Sebastian Thrun,</a>
                    <a class="pubauthor" href="http://cvgl.stanford.edu/silvio/">Silvio Savarese</a>
                </div>
                <div class="pubjournal">
                    Robotics: Science and Systems
                    (RSS), 2014
                </div>
                <!--a href="anytime_tracking.html" fontsize="10">[Project Page]</a-->
                <div id="abs2014rss" style="display:none">
                    <blockquote>
                        Although object tracking has been studied for decades, real-time tracking algorithms often suffer from low accuracy and poor robustness when confronted with difficult, real-world data. We present a tracker that combines 3D shape, color (when available), and motion cues to accurately track moving objects in real-time. Our tracker allocates computational effort based on the shape of the posterior distribution. Starting with a coarse approximation to the posterior, the tracker successively refines this distribution, increasing in tracking accuracy over time. The tracker can thus be run for any amount of time, after which the current approximation to the posterior is returned. Even at a minimum runtime of 0.7 milliseconds, our method outperforms all of the baseline methods of similar speed by at least 10%. If our tracker is allowed to run for longer, the accuracy continues to improve, and it continues to outperform all baseline methods. Our tracker is thus anytime, allowing the speed or accuracy to be optimized based on the needs of the application.
                    </blockquote>
                </div>
                <div id="bib2014rss" style="display:none">
                    <blockquote>
                        <pre>@INPROCEEDINGS{Held-RSS-14,
                            AUTHOR    = {David Held AND Jesse Levinson AND Sebastian Thrun AND Silvio Savarese},
                            TITLE     = {Combining 3D Shape, Color, and Motion for Robust Anytime Tracking},
                            BOOKTITLE = {Proceedings of Robotics: Science and Systems},
                            YEAR      = {2014},
                            ADDRESS   = {Berkeley, USA},
                            MONTH     = {July} } </pre>
                    </blockquote>
                </div>
                <div class="pubspan">
                    [<a href="javascript:copy(div2014rss, abs2014rss)">abstract</a>]
                    [<a href="javascript:copy(div2014rss, bib2014rss)">bibtex</a>]
                    [<a href="anytime_tracking.html">Project Page</a>]
                </div>
                <div id="div2014rss" class="pubInfo"></div>
                <!--/li-->
            </div>
        </td>
    </tr>
    <!-- <tr class="year"><td><li class="year">2013</li></td></tr> -->
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/3DModels.png" height="120">
        </td>
        <td class="pubitem">
            <div class="pubitem">
                <a class="pubtitle" href="DavidHeld_files/ICRA13_0624_FI.pdf">Precision Tracking with Sparse 3D and Dense Color 2D Data - <award>Best Vision Paper Finalist</award></a>
                <div>
                    <a class="pubauthor" href="http://stanford.edu/~davheld">David Held</a>,
                    <a class="pubauthor">Jesse Levinson</a>,
                    <a class="pubauthor" href="http://robots.stanford.edu/">Sebastian Thrun</a>
                </div>
                <div class="pubjournal">
                    International Conference on Robotics and Automation
                    (ICRA), 2013
                </div>
                <div id="abs2013icra" style="display:none">
                    <blockquote>
                        Precision tracking is important for predicting the
                        behavior of other cars in autonomous driving. We present a
                        novel method to combine laser and camera data to achieve
                        accurate velocity estimates of moving vehicles. We combine
                        sparse laser points with a high-resolution camera image to
                        obtain a dense colored point cloud. We use a color-augmented
                        search algorithm to align the dense color point clouds from
                        successive time frames for a moving vehicle, thereby obtaining
                        a precise estimate of the tracked vehicle’s velocity. Using this
                        alignment method, we obtain velocity estimates at a much
                        higher accuracy than previous methods. Through pre-ﬁltering,
                        we are able to achieve near real time results. We also present an
                        online method for real-time use with accuracies close to that of
                        the full method. We present a novel approach to quantitatively
                        evaluate our velocity estimates by tracking a parked car in
                        a local reference frame in which it appears to be moving
                        relative to the ego vehicle. We use this evaluation method to
                        automatically quantitatively evaluate our tracking performance
                        on 466 separate tracked vehicles. Our method obtains a mean
                        absolute velocity error of 0.27 m/s and an RMS error of 0.47
                        m/s on this test set. We can also qualitatively evaluate our
                        method by building color 3D car models from moving vehicles.
                        We have thus demonstrated that our method can be used for
                        precision car tracking with applications to autonomous driving
                        and behavior modeling.
                    </blockquote>
                </div>
                <div id="bib2013icra" style="display:none">
                    <blockquote>
                        <pre>@inproceedings{2013-held-precision,
                            title = {Precision Tracking with Sparse 3D and Dense Color 2D Data},
                            author = {David Held and Jesse Levinson and Sebastian Thrun},
                            booktitle = {ICRA},
                            year = {2013} }</pre>
                    </blockquote>
                </div>
                <div class="pubspan">
                    [<a href="javascript:copy(div2013icra, abs2013icra)">abstract</a>]
                    [<a href="javascript:copy(div2013icra, bib2013icra)">bibtex</a>]
                    [<a href="anytime_tracking.html">Project Page</a>]
                </div>
                <div id="div2013icra" class="pubInfo"></div>
                <!--/li-->
            </div>
        </td>
    </tr>
    <!-- ------------------------------------------------------------------------
        2012
        --------------------------------------------------------------------- -->
    <!-- <tr class="year"><td><li class="year">2012</li></td></tr> -->
    <!--
        2012 Car Detection (ICRA)
        -->
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/distanceScores.jpg" width="180">
        </td>
        <td class="pubitem">
            <div class="pubitem">
                <a class="pubtitle" href="papers/scaleDetection.pdf">A Probabilistic Framework for Car Detection in Images using Context and Scale</a>
                <!-- Official link: http://ieeexplore.ieee.org/xpls/abs_all.jsp?arnumber=6224722 -->
                <div>
                    <a class="pubauthor" href="http://stanford.edu/~davheld">David Held</a>,
                    <a class="pubauthor">Jesse Levinson</a>,
                    <a class="pubauthor" href="http://robots.stanford.edu/">Sebastian Thrun</a>
                </div>
                <div class="pubjournal">
                    International Conference on Robotics and Automation
                    (ICRA), 2012
                </div>
                <div id="abs2010emnlp" style="display:none">
                    <blockquote>
                        Detecting cars in real-world images is an important task for autonomous driving, yet it remains unsolved. The system described in this paper takes advantage of context and scale to build a monocular single-frame image-based car detector that significantly outperforms the baseline. The system uses a probabilistic model to combine multiple forms of evidence for both context and scale to locate cars in a real-world image. We also use scale filtering to speed up our algorithm by a factor of 3.3 compared to the baseline. By using a calibrated camera and localization on a road map, we are able to obtain context and scale information from a single image without the use of a 3D laser. The system outperforms the baseline by an absolute 9.4% in overall average precision and 11.7% in average precision for cars smaller than 50 pixels in height, for which context and scale cues are especially important.
                    </blockquote>
                </div>
                <div id="bib2010emnlp" style="display:none">
                    <blockquote>
                        <pre>@INPROCEEDINGS{6224722,
                            author={Held, D. and Levinson, J. and Thrun, S.},
                            booktitle={Robotics and Automation (ICRA), 2012 IEEE International Conference on}, title={A probabilistic framework for car detection in images using context and scale},
                            year={2012},
                            month={may},
                            volume={},
                            number={},
                            pages={1628 -1634},
                            keywords={Cameras;Computational modeling;Context;Context modeling;Detectors;Roads;Training;automobiles;object detection;probability;traffic engineering computing;autonomous driving;car detection;context information;monocular single-frame image-based car detector;probabilistic framework;scale filtering;scale information;},
                            doi={10.1109/ICRA.2012.6224722},
                            ISSN={1050-4729}
                            }</pre>
                    </blockquote>
                </div>
                <div class="pubspan">
                    [<a href="javascript:copy(div2010emnlp, abs2010emnlp)">abstract</a>]
                    [<a href="javascript:copy(div2010emnlp, bib2010emnlp)">bibtex</a>]
                    [<a href="papers/scaleDetection.pdf">Full Paper</a>]
                </div>
                <div id="div2010emnlp" class="pubInfo"></div>
            </div>
        </td>
    </tr>
    <tr>
        <td>
            <li class="year"> Older Work </li>
        </td>
    </tr>
    <!--
        2012 Octopus (ICRA)
        -->
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/armforce.png" width="180">
        </td>
        <td class="pubitem">
            <div class="pubitem">
                <a class="pubtitle" href="papers/ICRA12_1385_FI.pdf">Characterizing Stiffness of Multi-Segment Flexible Arm Movements</a>
                <!-- Official link: http://ieeexplore.ieee.org/xpls/abs_all.jsp?arnumber=6225070 -->
                <div>
                    <a class="pubauthor" href="http://stanford.edu/~davheld">David Held</a>,
                    Yoram Yekutieli,
                    <a class="pubauthor" href="http://www.wisdom.weizmann.ac.il/~tamar/">Tamar Flash</a>
                </div>
                <div class="pubjournal">
                    International Conference on Robotics and Automation
                    (ICRA), 2012
                </div>
                <div id="abs2012octopus" style="display:none">
                    <blockquote>
                        A number of robotic studies have recently turned to biological inspiration in designing control schemes for flexible robots. Examples of such robots include continuous manipulators inspired by the octopus arm. However, the control strategies used by an octopus in moving its arms are still not fully understood. Starting from a dynamic model of an octopus arm and a given set of muscle activations, we develop a simulation technique to characterize the stiffness throughout a motion and at multiple points along the arm. By applying this technique to reaching and bending motions, we gain a number of insights that can help a control engineer design a biologically inspired impedance control scheme for a flexible robot arm. The framework developed is a general one that can be applied to any motion for any dynamic model. We also propose a theoretical analysis to efficiently estimate the stiffness analytically given a set of muscle activations. This analysis can be used to quickly evaluate the stiffness for new static configurations and dynamic movements.
                    </blockquote>
                </div>
                <div id="bib2010octopus" style="display:none">
                    <blockquote>
                        <pre>@INPROCEEDINGS{6225070,
                            author={Held, D. and Yekutieli, Y. and Flash, T.},
                            booktitle={Robotics and Automation (ICRA), 2012 IEEE International Conference on}, title={Characterizing the stiffness of a multi-segment flexible arm during motion},
                            year={2012},
                            month={may},
                            volume={},
                            number={},
                            pages={3825 -3832},
                            keywords={Computational modeling;Force;Motion segmentation;Muscles;Shape;Trajectory;control system synthesis;dexterous manipulators;elasticity;flexible manipulators;manipulator dynamics;motion control;muscle;bending motion control;biologically inspired impedance control;control scheme design;dynamic movement;multisegment flexible robot arm;muscle activation;octopus arm;robot dynamic model;stiffness;},
                            doi={10.1109/ICRA.2012.6225070},
                            ISSN={1050-4729}
                            }</pre>
                    </blockquote>
                </div>
                <div class="pubspan">
                    [<a href="javascript:copy(div2012octopus, abs2012octopus)">abstract</a>]
                    [<a href="javascript:copy(div2012octopus, bib2010octopus)">bibtex</a>]
                    [<a href="papers/ICRA12_1385_FI.pdf">Full Paper</a>]
                </div>
                <div id="div2012octopus" class="pubInfo"></div>
            </div>
        </td>
    </tr>
    <!-- ------------------------------------------------------------------------
        2011
        --------------------------------------------------------------------- -->
    <!--li class="year"> 2011 </li-->
    <!--
        2011 Driving
        -->
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/Junior.png" width="180">
        </td>
        <td class="pubitem">
            <div class="pubitem">
                <a class="pubtitle" href="http://ieeexplore.ieee.org/xpls/abs_all.jsp?arnumber=5940562">Towards fully autonomous driving: Systems and algorithms</a>
                <div>
                    Jesse Levinson, Jake Askeland, Jan Becker, Jennifer Dolson, <a class="pubauthor" href="http://stanford.edu/~davheld">David Held</a>, Soeren Kammel,
                    J. Zico Kolter, Dirk Langer, Oliver Pink, Vaughan Pratt, Michael Sokolsky,
                    Ganymed Stanek, David Stavens, Alex Teichman, Moritz Werling, and Sebastian Thrun
                </div>
                <div class="pubjournal">
                    Intelligent Vehicles Symposium (IV), 2011.
                </div>
                <div id="abs2011IV" style="display:none">
                    <blockquote>
                        In order to achieve autonomous operation of a vehicle in urban situations with unpredictable traffic, several realtime systems must interoperate, including environment perception, localization, planning, and control. In addition, a robust vehicle platform with appropriate sensors, computational hardware, networking, and software infrastructure is essential. We previously published an overview of Junior, Stanford's entry in the 2007 DARPA Urban Challenge. This race was a closed-course competition which, while historic and inciting much progress in the field, was not fully representative of the situations that exist in the real world. In this paper, we present a summary of our recent research towards the goal of enabling safe and robust autonomous operation in more realistic situations. First, a trio of unsupervised algorithms automatically calibrates our 64-beam rotating LIDAR with accuracy superior to tedious hand measurements. We then generate high-resolution maps of the environment which are subsequently used for online localization with centimeter accuracy. Improved perception and recognition algorithms now enable Junior to track and classify obstacles as cyclists, pedestrians, and vehicles; traffic lights are detected as well. A new planning system uses this incoming data to generate thousands of candidate trajectories per second, choosing the optimal path dynamically. The improved controller continuously selects throttle, brake, and steering actuations that maximize comfort and minimize trajectory error. All of these algorithms work in sun or rain and during the day or night. With these systems operating together, Junior has successfully logged hundreds of miles of autonomous operation in a variety of real-life conditions.
                    </blockquote>
                </div>
                <div id="bib2011IV" style="display:none">
                    <blockquote>
                        <pre>@INPROCEEDINGS{5940562,
                            author={Levinson, J. and Askeland, J. and Becker, J. and Dolson, J. and Held, D. and Kammel, S. and Kolter, J.Z. and Langer, D. and Pink, O. and Pratt, V. and Sokolsky, M. and Stanek, G. and Stavens, D. and Teichman, A. and Werling, M. and Thrun, S.},
                            booktitle={Intelligent Vehicles Symposium (IV), 2011 IEEE}, title={Towards fully autonomous driving: Systems and algorithms},
                            year={2011},
                            month={june},
                            volume={},
                            number={},
                            pages={163 -168},
                            keywords={Calibration;Laser beams;Planning;Software;Trajectory;Vehicle dynamics;Vehicles;computer vision;mobile robots;remotely operated vehicles;DARPA urban challenge;LIDAR;autonomous driving;closed-course competition;environment perception;obstacle classification;obstacle tracking;online localization;planning system;realtime system;recognition algorithm;robust autonomous operation;robust vehicle platform;software infrastructure;unpredictable traffic;},
                            doi={10.1109/IVS.2011.5940562},
                            ISSN={1931-0587}}</pre>
                    </blockquote>
                </div>
                <div class="pubspan">
                    [<a href="javascript:copy(div2011IV, abs2011IV)">abstract</a>]
                    [<a href="javascript:copy(div2011IV, bib2011IV)">bibtex</a>]
                </div>
                <div id="div2011IV" class="pubInfo"></div>
            </div>
        </td>
    </tr>
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/hovercraft.png" width="180">
        </td>
        <td class="pubitem">
            <div class="pubitem">
                <a class="pubtitle" href="papers/jin+04-acc.pdf">MVWT-II: The Second Generation Caltech Multi-Vehicle Wireless Testbed</a>
                <!-- Official link: http://ieeexplore.ieee.org/xpls/abs_all.jsp?arnumber=1384698 -->
                <div class="pubauthor">
                    Zhipu Jinh,  Stephen Waydo,  Elisabeth B. Wildanger,  Michael Lammers,
                    Hans Scholze, Peter Foley,
                    <a class="pubauthor" href="http://stanford.edu/~davheld">David Held</a>,
                    Richard M. Murray
                </div>
                <div class="pubjournal">
                    American Control Conference (ACC), 2004
                </div>
                <div id="abs2004acc" style="display:none">
                    <blockquote>
                        The Caltech Multi-Vehicle Wireless Testbed is an experimental platform for validating theoretical advances in multiple-vehicle coordination and cooperation, real-time networked control system, and distributed computation. This paper describes the design and development of an additional fleet of 12 second-generation vehicles. These vehicles are hovercrafts and designed to have lower mass and friction as well as smaller size than the first generation vehicles. These hovercrafts combined with the outdoor wireless testbed provide a perfect hardware platform for RoboFlag competition.
                    </blockquote>
                </div>
                <div id="bib2004acc" style="display:none">
                    <blockquote>
                        <pre>@INPROCEEDINGS{1384698,
                            author={Jin, Z. and Waydo, S. and Wildanger, E.B. and Lammers, M. and Scholze, H. and Foley, P. and Held, D. and Murray, R.M.},
                            booktitle={American Control Conference, 2004. Proceedings of the 2004}, title={MVWT-II: the second generation Caltech Multi-Vehicle Wireless Testbed},
                            year={2004},
                            month={30 2004-july 2},
                            volume={6},
                            number={},
                            pages={5321 -5326 vol.6},
                            keywords={design engineering;games of skill;hovercraft;mobile robots;multi-robot systems;real-time systems;Caltech MultiVehicle Wireless Testbed;RoboFlag competition;distributed computation;hardware platform;hovercraft design;multivehicle cooperation;multivehicle coordination;outdoor wireless testbed;real time networked control system;second generation vehicles;},
                            doi={},
                            ISSN={0743-1619}}</pre>
                    </blockquote>
                </div>
                <div class="pubspan">
                    [<a href="javascript:copy(div2004acc, abs2004acc)">abstract</a>]
                    [<a href="javascript:copy(div2004acc, bib2004acc)">bibtex</a>]
                </div>
                <div id="div2004acc" class="pubInfo"></div>
            </div>
        </td>
    </tr>
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/tactors.png" width="180">
                <!--img src="DavidHeld_files/tactors.png" width="180"-->
                </td>
        <td class="pubitem">
            <div class="pubitem">
                <a class="pubtitle" href="papers/78658.pdf">Surface waves and spatial localization in vibrotactile displays</a>
                <!-- Official link: http://ieeexplore.ieee.org/xpls/abs_all.jsp?arnumber=5444673 -->
                <div>
                    <a class="pubauthor" href="http://meche.mit.edu/people/index.html?id=128">Lynette Jones</a>,
                    <a class="pubauthor" href="http://stanford.edu/~davheld">David Held</a>,
                    <a class="pubauthor" href="http://meche.mit.edu/people/index.html?id=46">Ian Hunter</a>
                </div>
                <div class="pubjournal">
                    Haptics Symposium, 2010
                </div>
                <div id="abs2010vibrations" style="display:none">
                    <blockquote>
                        The locus of vibrotactile stimulation is often used as an encoding cue in tactile displays developed for spatial orientation and navigation. However, the ability to localize the site of stimulation varies as a function of the number and configuration of the vibrating motors (tactors) in the display. As the inter-tactor distance decreases it has been found that the ability to localize a point of stimulation diminishes. One factor that may limit tactile localization is the surface wave elicited by vibration that propagates across the skin at a velocity that depends on the frequency of vibration and the viscoelastic properties of the skin. A material that simulates the stress-strain characteristics of human skin was used to measure the characteristics of surface waves during vibrotactile stimulation. Accelerometers glued to the simulated skin at fixed distances from the activated tactors were used to measure the amplitude of the acceleration as a function of distance as well as the propagation velocity. It was determined that at a distance of 60 mm from the site of activation, the surface wave was on average attenuated to less than 1 m/s^2. This suggests that for this type of tactor an inter-tactor distance of at least 60 mm would be optimal for a display in which the locus of stimulation is used as an encoding variable. It seems that much of the difficulty encountered in identifying the locus of a vibrotactile stimulus in multi-tactor displays may result from small intertactor distances.
                    </blockquote>
                </div>
                <div id="bib2010vibrations" style="display:none">
                    <blockquote>
                        <pre>@INPROCEEDINGS{5444673,
                            author={Jones, L.A. and Held, D. and Hunter, I.},
                            booktitle={Haptics Symposium, 2010 IEEE}, title={Surface waves and spatial localization in vibrotactile displays},
                            year={2010},
                            month={march},
                            volume={},
                            number={},
                            pages={91 -94},
                            keywords={Accelerometers;Displays;Elasticity;Encoding;Frequency;Humans;Navigation;Skin;Surface waves;Viscosity;accelerometers;haptic interfaces;accelerometers;distance 60 mm;inter-tactor distance;spatial localization;stimulation locus;stress-strain characteristics;surface waves;vibrating motors;vibrotactile displays;vibrotactile stimulation;localization;tactile display;tactons;torso;touch;},
                            doi={10.1109/HAPTIC.2010.5444673},
                            ISSN={}}</pre>
                    </blockquote>
                </div>
                <div class="pubspan">
                    [<a href="javascript:copy(div2010vibrations, abs2010vibrations)">abstract</a>]
                    [<a href="javascript:copy(div2010vibrations, bib2010vibrations)">bibtex</a>]
                </div>
                <div id="div2010vibrations" class="pubInfo"></div>
            </div>
        </td>
    </tr>
    <tr>
        <td class="pubimg">
            <img src="../DavidHeld_files/tactors1.png" width="180">
            <!--img src="DavidHeld_files/tactors1.png" width="180"-->
        </td>
        <td class="pubitem">
            <div class="pubitem">
                <a class="pubtitle" href="http://computingengineering.asmedigitalcollection.asme.org/article.aspx?articleid=1401367">Characterization of Tactors Used in Vibrotactile Displays</a>
                <div>
                    <a class="pubauthor" href="http://meche.mit.edu/people/index.html?id=128">Lynette Jones</a>,
                    <a class="pubauthor" href="http://stanford.edu/~davheld">David Held</a>
                </div>
                <div class="pubjournal">
                    Journal of Computing and Information Science in Engineering, 2008
                </div>
                <div id="abs2008jcis" style="display:none">
                    <blockquote>
                        A series of experiments was conducted to evaluate the operating characteristics of small DC motors that are often in tactile displays. The results indicated that these motors are reliable in terms of their frequency and amplitude of oscillation, but that the frequency varies across motors. A simulated skin material was developed to provide a substrate for evaluating the performance of the motors. There was a marked attenuation in frequency when the tactors were on this material and the surface waves could be detected 60 mm from the site of activation. These findings suggest that the spacing between tactors should be at least 60-80 mm if tactile cues are used to locate events in the environment.
                    </blockquote>
                </div>
                <div id="bib2008jcis" style="display:none">
                    <blockquote>
                        <pre>@article{jones_held:044501,
                            author = {Lynette A. Jones and David A. Held},
                            collaboration = {},
                            title = {Characterization of Tactors Used in Vibrotactile Displays},
                            publisher = {ASME},
                            year = {2008},
                            journal = {Journal of Computing and Information Science in Engineering},
                            volume = {8},
                            number = {4},
                            eid = {044501},
                            numpages = {5},
                            pages = {044501},
                            keywords = {DC motors; display devices; haptic interfaces},
                            url = {http://link.aip.org/link/?CIS/8/044501/1},
                            doi = {10.1115/1.2988384}
                            }</pre>
                    </blockquote>
                </div>
                <div class="pubspan">
                    [<a href="javascript:copy(div2008jcis, abs2008jcis)">abstract</a>]
                    [<a href="javascript:copy(div2008jcis, bib2008jcis)">bibtex</a>]
                </div>
                <div id="div2008jcis" class="pubInfo"></div>
            </div>
        </td>
    </tr>
    </table>
<!-- </div> -->
<!-- ------------------------------------------------------------------------
    YEAR
    --------------------------------------------------------------------- -->
<!--li class="year"> YEAR </li-->
<!--
    ENTRY NAME
    -->
<!--li class="pubitem">
    <a class="pubtitle" href="">TITLE</a>
    <div>
    <a class="pubauthor" href="http://stanford.edu/~davheld">David Held</a>,
    OTHER AUTHORS
    </div>
    <div class="pubjournal">
    CONFERENCE NAME (ABBREVIATION). YEAR
    </div>
    <div id="absNEW" style="display:none">
    <blockquote>
    ABSTRACT
    </blockquote>
    </div>
    <div id="bibNEW" style="display:none">
    <blockquote>
    <pre> BIBTEX</pre>
    </blockquote>
    </div>
    <div class="pubspan">
    [<a href="javascript:copy(divNEW, absNEW)">abstract</a>]
    [<a href="javascript:copy(divNEW, bibNEW)">bibtex</a>]
    </div>
    <div id="divNEW" class="pubInfo"></div>
    </li-->
<!--/ul-->
<!--/tr-->

<!--div class="heading"> Pre-Prints </div>


<table cellpadding="10" width="100%">
    
</table-->
<!-- Add this to a new tab later
<div class="heading"> Advice </div>



    table cellpadding="10" width="100%">
    
    <tr>
        <td>
            I gave a talk on <a href="https://www.youtube.com/watch?v=CDXZXljc2Ic">"Demystifying the Post-doc - Why, Where, and How?"</a>  If you are considering doing a post-doc, the advice in this talk might be helpful.
            
            In this talk, I describe the ins and outs of getting a job as a post-doctoral researcher ("doing a post-doc").  I first describe a number of reasons why one might want to do a post-doc, as well as a few reasons not to do one.  I next describe how to choose where one should apply for a post-doc.  Next, I describe the process of how to get a job in a dream post-doc position.  I also describe how to choose among multiple post-doc offers.  Last, I will describe how to be "successful" as a post-doc, i.e. how to make the most of your time as a post-doc and prepare for your future career.  You can watch this video
        </td>
    </tr>
</table> -->
<!--END CONTENT-->
<!-- <div style="clear: both;"></div> -->
<!-- </div> -->
<!-- Preprints -->


<div class="heading"> Preprints </div>
<div>
    <table cellpadding="10" text-align="left" width="100%">
        <!-- <tr><td><li class="year"> 2017</li></td></tr> -->
        <tr>
            <td class="pubimg" width="250" height="100">
                <img src="../DavidHeld_files/indicator2019.png" img width="250">
            </td>
            <td><a href="https://arxiv.org/abs/1905.07866">Reinforcement Learning without Ground-Truth State</a><br>
                <div class="pubauthor">
                    Xingyu Lin, Harjatin Singh Baweja, David Held<br>
                </div>
                <br>
            </td>
        </tr>
        <tr>
            <td class="pubimg" width="250" height="100">
                <img src="../DavidHeld_files/itn2018.png" width="250" height="100">
            </td>
            <td><a href="https://arxiv.org/abs/1811.11209">Iterative Transformer Network for 3D Point Cloud</a><br>
                <div class="pubauthor">
                    Wentao Yuan, David Held, Christoph Mertz, Martial Hebert<br>
                </div>
                <br>
            </td>
        </tr>
    </table>
</div>
<p></p>
