DECLARE @Syntax VARCHAR(MAX)

IF EXISTS (SELECT 1 FROM [master].[sys].[availability_groups_cluster])
	BEGIN

SELECT @Syntax = '#####  ' + cluster_name + ' #####' + CHAR(13) + CHAR(10)
		+ CHAR(13) + CHAR(10)
		+ 'Import-Module FailoverClusters' + CHAR(13) + CHAR(10)
		+ '$ClusNode = "' + cluster_name + '"' + CHAR(13) + CHAR(10)
		+ '$CyrusNode = "' + REPLACE(cluster_name,'CR1','SR1') + '"' + CHAR(13) + CHAR(10)
		+ '$LBNode = "' + REPLACE(cluster_name,'CR1','SR2') + '"' + CHAR(13) + CHAR(10)
		+ CHAR(13) + CHAR(10)
		+ 'Stop-ClusterNode –Name $LBNode' + CHAR(13) + CHAR(10)
		+ 'Get-Service -name ClusSvc -ComputerName $LBNode | Stop-Service' + CHAR(13) + CHAR(10)
		+ CHAR(13) + CHAR(10)
		+ '# Verify the Cluster service is stopped' + CHAR(13) + CHAR(10)
		+ 'Get-Service -name ClusSvc -ComputerName $LBNode' + CHAR(13) + CHAR(10)
		+ CHAR(13) + CHAR(10)
		+ 'Start-ClusterNode -Cluster $ClusNode –Name $LBNode -FixQuorum'  
		+ CHAR(13) + CHAR(10)
		+ '# Verify the cluster node is UP' + CHAR(13) + CHAR(10)
		+ 'Get-ClusterNode $LBNode' + CHAR(13) + CHAR(10)
		+ 'Get-ClusterGroup -Cluster $ClusNode' + CHAR(13) + CHAR(10)
		+ CHAR(13) + CHAR(10)
		+ '# Set the node quorum vote to 1' + CHAR(13) + CHAR(10)
		+ '(Get-ClusterNode -Cluster $ClusNode -name $LBNode).NodeWeight = 1' + CHAR(13) + CHAR(10)
		+ 'Get-ClusterNode -Cluster $ClusNode | SELECT -property NodeName, State, NodeWeight, DynamicWeight | FT' + CHAR(13) + CHAR(10)
		+ CHAR(13) + CHAR(10)
FROM sys.dm_hadr_cluster
WHERE REPLACE(cluster_name,'CR1','SR1') = CASE 
											WHEN CHARINDEX('\',@@SERVERNAME) > 0
												THEN LEFT(@@SERVERNAME,CHARINDEX('\',@@SERVERNAME)-1)
											ELSE @@SERVERNAME
											END

	END
SELECT @Syntax AS [Syntax]