#####  CSQL1 #####

Import-Module FailoverClusters
$ClusNode = "CSQL1"
$CyrusNode = "DC1SQL1"
$LBNode = "DC2SQL1"

Stop-ClusterNode –Name $LBNode
Get-Service -name ClusSvc -ComputerName $LBNode | Stop-Service

# Verify the Cluster service is stopped
Get-Service -name ClusSvc -ComputerName $LBNode

Start-ClusterNode -Cluster $ClusNode –Name $LBNode -FixQuorum
# Verify the cluster node is UP
Get-ClusterNode $LBNode
Get-ClusterGroup -Cluster $ClusNode

# Set the node quorum vote to 1
(Get-ClusterNode -Cluster $ClusNode -name $LBNode).NodeWeight = 1
Get-ClusterNode -Cluster $ClusNode | SELECT -property NodeName, State, NodeWeight, DynamicWeight | FT

