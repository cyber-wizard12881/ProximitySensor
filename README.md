# ProximitySensor
KNN Range Search based on KdTree as the Backing Data Structure

**What is KNN anyways? <br>**
K --> Number of Dimensions <br>
NN --> Nearest Neighbors <br>

**Hmmm ... then What is a KNN Search? <br>**
KNN Search is an Algorithm that enables you to find Nearest Neighbors in a K Dimensional Data Set! <br>

**How the heck does it work? <br>**
It uses a KD Tree as a backing data store Data Structure! <br>

**Now, what is a KD Tree anyways? <br>**
It's a K-Dimensional Analog of a Normal Binary Search Tree! <br>

**What are it's constituents?<br>**
It consists of basically two types of Nodes .... <br>
<1>Bounding Boxes [Non-Leaf Nodes] <br>
<2>Point Nodes [Leaf Nodes] <br>

At each Level of the KD Tree, there are Cut-Dimensions that cycle alternately between the K Dimensions! <br>

For eg. in a K=2 i.e a Planar Structure .... <br>
At Root-Level (0) ==> Cut-Dimension = X-Axis <br>
At Level (1) ==> Cut-Dimension = Y-Axis <br>
At Level (2) ==> Cut-Dimension = X-Axis .... and So On .... <br>

**So, How do we Traverse a KD Tree? <br>**
We Start from the Root or any Concerned Node .... <br>
Determine the Cut-Dimension .... and check just like we do in a BST .... if the Point's Concerned Dimension Value is Less Than that of Cut-Dimension Value ..... go ==> Node->Left .... else go ==> Node->Right!!! <br>
We do this exercise till we reach a Leaf Node ... which is the Actual Point & then We check if the Point's Value is the same as that of the Search Point Value or Not!<br>

**But....there's a catch!!?? <br>**
We need to Search the other Half of the Sub Tree if the Cut-Dimension Level is not the One We are Searching For!!! <br>

**Back to the KNN Search....<br>**
We are using the Version of the KNN Search called Range Based Searching!!! <br>

**Okay ... so How's that different from the Regular KNN Search? <br> ... & what on earth is a Range here? <br>**
In this version of the Search called KNN Range Based Searching .... we have the Following .... <br>
0. K ==> 2 for example a 2-D Cartesian Plane. <br>
1. Points[] ==> Set or Vector of Points (random) in a Plane. <br>
2. Range ==> A Range to search for eg. [1,2] --> [5,8] .... a Rectangular Region within which we wish to find all the points that lie completely within or on it!!! <br>
3. Region ==> A Outer Clipping Window or Bounds for the KD Tree ... for eg. [0,0] --> [21,21] <br>
4. The KD Tree ==> Like Described above .. storing all Points[] in it's respective Leaf Nodes!!!! <br>

**Alright!!....Coming to the Code Now.... What do we have to explore now? ..... <br>**
This Implementation is Divided into 3 parts ..... <br>
1. Serial Version of KNN Range Based Search <br>
2. Pseudo-Parallel Version of the KNN Range Based Search <br>
3. Parallel Version of the KNN Range Based Search <br>

**Hmmm .... how are they different from each other? <br>**
1. The Serial One ===> uses Naive Serial Tree Building & Searching!!!.... with Normal Serial Containers .... vector<int> for instance! <br>
2. The Pseudo-Parallel One ==> Uses the Naive Serial Tree Building Structures (Containers) ... but runs the Build in Parallel!!! & the Search is using Parallel Containers!!! <br>
3. Parallel One ==> Uses Completely Parallel Containers for Tree Building & Searching as well!!!! <br>

**Structure of this Repository is as follows.... <br>**
1. ProximitySensor ===> the Main Driver Solution ... which runs all the 3 versions on the Algorithms as discussed above with results and timings!!! .... This is where to get Started ..... <br>
2. KNN ===> The DLL for KNN Search .... all the 3 .... Serial, Pseudo-Parallel & Parallel Versions of Them!!! <br>
3. KDTree ===> The DLL for the KD Tree .... both the versions ... Serial as well as the Parallel Versions of them!!! <br>

**Wow!!!... So what's special about the Parallel Versions of the Algorithms? <br>**
Simply 3 things only ..... <br>
1. They used Data Partitioning of Chunks of Point[] based on N=4 for instance!!! <br>
2. Build Parallel KNN Objects using Parallel Containers ... like concurrent_vector<int> etc... <br>
3. Run parallel_for internally for each of the Parallel KD Tree Structures & the KNN Search Functions!!!! <br>

**Ok...So what's the use of this KNN Search thingy anyways? <br>**
Giving a very Crude Example .... <br>
If we want to find People with similar tastes for example .... <br>
1. The Food & Drinks they like .... <br>
2. The Songs they listen to .... <br>
3. The Movies they watch .... <br>
4. The Books they read ... <br>
..... etc. ... <br>
This becomes for instance a 4-Dimensional Search Problem .... <br> .... with each of the above Parameters or Interests .. We can find the closest such People with matching tastes ... using the KNN Range Based Search Algorithm ....!!!! <br>

**There's More .... <br>**
Based on the Thresholds we set we can expand or contract our region to find the Nearest Neighbors and the people with similar tastes .... <br>
Also, taking it one step further .... we can even do Auto Suggestions based on this data for similar people are More likely to have similar tastes .... <br>
The above falls into Data Science & AI & ML .... <br>

**Cool....This is not Rocket Science anymore ... !!! <br>**
So, by using the KNN Range Based Search one can easily find out the Nearest Neighbors ... This has numerous applications in Business as mentioned above ... and in Computational Geometry ... Crude .... Algorithms .. like finding Nearest Points in a 2-D Plane or 3-D Space or for that matter even 1-D Line ... !!!! <br>

**What Next??? <br>**
Go through the Code .... explore the Implementation .... !!! <br> AND .... <br>
Do Not Forget to Run it on your System!!! <br>
Play with it ... <br>
Tinker with it ... <br>
Tune the Parameters and see how it behaves .... <br>
& .... <br>
Feel free to improvise and see if you can extend this to other forms and applications as well!!! ... <br>

**A Glimpse at the Output .... To get you Started!!! <br>**
![Output of KNN Search Program](Output.PNG)   <br>

**Wrapping Things Up!!! <br>**
I Hope that this Personal Project of Mine would have shed light on the Intricacies of the KNN Range Based Search Using KD Trees and it's Parallel Versions given some rationale of how to Parallelize Algorithms esp. using the Parallel Patterns Library in VC++ .... <br>

**I hope you guys would have found this Project Useful..!!!! <br>**
So, my request to you avid programmers out there is to take this to the next level or implement something on similar lines in the language of your choice or liking!!! <br>

**That's All Folks!!! .... <br>**

Have a Great Time with KNN Searches!!! <br>

& <br>

Happy Coding!!! <br>

:-) <br>

Best Regards, <br>
Bhaskar Rao.
