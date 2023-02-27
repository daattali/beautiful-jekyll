---
layout: post
title:  "MSBuild's cool feature - Directory.Build.props and Directory.Build.targets"
date:   2023-02-25 11:23:21 AM
categories: [Build, MsBuild]
---

Recently I had to work on enabling the Code Analysis on a project we recently started. We should have ideally done it from the very start but better late than never.

With the Roslyn Code Analyzers, Code analysis is very powerful and provides very good suggestions/warning in the code. I recommend enabling these to keep the coding style consistent and also to keep the product code quality.

I have been developing on .Net Framework from a while and I am surprised that I never used the cool features of MSBuild. For enabling the Code Analysis, we have perform the following steps:

1. Install Microsoft.CodeAnalysis.NetAnalyzers package on all the Projects in the solution.
2. Set some properties at the Project level to enable the Analyzers and to report the suggestions as either Warning or Error etc.

Doing this on all the projects individually is not the best way to solve this. It would be great if we can do this at a centralized place and have those setting propagate to the individual projects. This is where the MSBuilds Directory.Build.Props comes very handy.

I have been developing on .Net Framework from a while and I was surprised that I never used the cool features of MSBuild. 

1. Directory.Build.Props
2. Directory.Build.Targets

Directory.Build.Props is a special file that you can create and drop it at the directory level. In this file you can define Property groups, Item Property, PackageReference etc. When Msbuild build's the project, it will check for this file in the current folder and then go up the folder hierarchy to find this file and add whats defined in it to the project its building. So we can use this feature to add the Analyzers for all project and enable it.

Below the Directory.Build.props file example 

```
<Project>
    <PropertyGroup>
        <EnableNETAnalyzers>true</EnableNETAnalyzers>
        <CodeAnalysisTreatWarningsAsErrors>true</CodeAnalysisTreatWarningsAsErrors>
        <AnalysisMode>AllEnabledByDefault</AnalysisMode>
    </PropertyGroup>
    <ItemGroup>
        <PackageReference Include="Microsoft.CodeAnalysis.NetAnalyzers"
                          Version="7.0.0"
                          PrivateAssets="All" />
    </ItemGroup>
</Project>
```

You can also use this feature to install common Nugets packages across all Projects For example : NewtonSoft etc.

!Happy Learning and improving one day at a time!



