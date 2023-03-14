<distribution version="17.0.0" name="EWD-EOMS" type="MSI">
	<prebuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></prebuild>
	<postbuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></postbuild>
	<msi GUID="{88548FF6-4DEF-450E-96D8-A4BC9B223BF0}">
		<general appName="EWD-EOMS" outputLocation="f:\EWD-EOMS\EWD-EOMS\EOMS\cvidistkit.EWD-EOMS" relOutputLocation="cvidistkit.EWD-EOMS" outputLocationWithVars="f:\EWD-EOMS\EWD-EOMS\EOMS\cvidistkit.%name" relOutputLocationWithVars="cvidistkit.%name" upgradeBehavior="1" autoIncrement="true" version="1.0.5">
			<arp company="华南师范大学彩色动态电子纸显示技术研究所" companyURL="" supportURL="" contact="" phone="" comments=""/>
			<summary title="" subject="" keyWords="" comments="" author=""/></general>
		<userinterface language="Chinese (Simplified)" showPaths="true" showRuntimeOnly="true" readMe="" license="">
			<dlgstrings welcomeTitle="EWD-EOMS" welcomeText=""/></userinterface>
		<dirs appDirID="100">
			<installDir name="[Program Files]" dirID="2" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="[Start&gt;&gt;Programs]" dirID="7" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="EWD-EOMS" dirID="100" parentID="2" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="EWD-EOMS" dirID="101" parentID="7" isMSIDir="false" visible="true" unlock="false"/></dirs>
		<files>
			<simpleFile fileID="0" sourcePath="f:\EWD-EOMS\EWD-EOMS\EOMS\cvibuild.EOMS\Release\EOMS.exe" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="1" sourcePath="f:\EWD-EOMS\EWD-EOMS\EOMS\ui\EOMS.uir" relSourcePath="ui\EOMS.uir" relSourceBase="0" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="2" sourcePath="f:\EWD-EOMS\EWD-EOMS\EOMS\ui\CVGraph.uir" relSourcePath="ui\CVGraph.uir" relSourceBase="0" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="3" sourcePath="f:\EWD-EOMS\EWD-EOMS\EOMS\ui\Entry.uir" relSourcePath="ui\Entry.uir" relSourceBase="0" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="4" sourcePath="f:\EWD-EOMS\EWD-EOMS\EOMS\ui\LCGraph.uir" relSourcePath="ui\LCGraph.uir" relSourceBase="0" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/></files>
		<fileGroups>
			<projectOutput targetType="0" dirID="100" projectID="0">
				<fileID>0</fileID></projectOutput>
			<projectDependencies dirID="100" projectID="0"/></fileGroups>
		<shortcuts>
			<shortcut name="EOMS" targetFileID="0" destDirID="101" cmdLineArgs="" description="" runStyle="NORMAL"/></shortcuts>
		<mergemodules/>
		<products/>
		<runtimeEngine installToAppDir="false" activeXsup="false" analysis="true" cvirte="true" dotnetsup="true" instrsup="true" lowlevelsup="false" lvrt="true" netvarsup="true" rtutilsup="false">
			<hasSoftDeps/>
			<doNotAutoSelect>
			<component>activeXsup</component>
			<component>lowlevelsup</component>
			<component>rtutilsup</component>
			</doNotAutoSelect></runtimeEngine><sxsRuntimeEngine>
			<selected>false</selected>
			<doNotAutoSelect>false</doNotAutoSelect></sxsRuntimeEngine>
		<advanced mediaSize="2048">
			<launchConditions>
				<condition>MINOS_WIN7_SP1</condition>
			</launchConditions>
			<includeConfigProducts>true</includeConfigProducts>
			<maxImportVisible>silent</maxImportVisible>
			<maxImportMode>merge</maxImportMode>
			<custMsgFlag>false</custMsgFlag>
			<custMsgPath>msgrte.txt</custMsgPath>
			<signExe>false</signExe>
			<certificate></certificate>
			<signTimeURL></signTimeURL>
			<signDescURL></signDescURL></advanced>
		<baselineProducts>
			<product name="NI-VISA Runtime 19.0" UC="{8627993A-3F66-483C-A562-0D3BA3F267B1}" productID="{EACEADFB-F69A-4FA2-8AF8-7A4A57C48A2D}" path="(None)" flavorID="_deployment_" flavorName="Runtime" verRestr="false" coreVer="19.0.49152">
				<dependencies>
					<productID>{0718DA15-62AE-42BF-BE2D-E1929A3E1099}</productID>
					<productID>{0EDC6197-1568-40AF-B31A-75DC08335991}</productID>
					<productID>{139B293A-1226-4199-AC8D-A238ADC86EB9}</productID>
					<productID>{188FE206-B0A6-43EB-85A3-37080D3E9CC2}</productID>
					<productID>{238429CC-CB53-434F-B446-C8281815057E}</productID>
					<productID>{26EE21C0-088A-4E92-A1CE-8535968CBF9C}</productID>
					<productID>{326C5DFC-D2BE-4CB4-B9EB-E55696D74837}</productID>
					<productID>{56835848-FC77-4EAC-8467-F5B3F25AF987}</productID>
					<productID>{5E39EF13-6B0A-4C7A-B7FB-608DB58D1D73}</productID>
					<productID>{64ECB814-3A6A-4E48-9D2F-D6C2EDD725B7}</productID>
					<productID>{69181DFA-D7CA-4AFE-98E2-A985F32B557B}</productID>
					<productID>{6EA91453-64A5-4024-BB1F-7E5BA38E22D1}</productID>
					<productID>{75747B47-816C-4D6C-907C-0BCD82AA9017}</productID>
					<productID>{76D52089-02AC-46AF-A013-F8206B55F722}</productID>
					<productID>{81710CDC-7B4D-4A91-8D44-8E2F8B5C2B6E}</productID>
					<productID>{820FB6E8-8856-48D7-934C-76169DCCFD48}</productID>
					<productID>{840E0F21-282D-4E7A-85BD-EF7D77FF8F6B}</productID>
					<productID>{88104A0D-1729-4A73-B798-80BEFC243F18}</productID>
					<productID>{8CA5A8AA-78BD-46D2-9C05-1C27D18AB913}</productID>
					<productID>{A242227B-C0A1-4F4C-9A71-217D1B19D347}</productID>
					<productID>{AF170C9E-251A-4F6A-B56A-AB62879FA6B2}</productID>
					<productID>{AFC999BB-F270-46EF-B748-AE755EC75322}</productID>
					<productID>{B29007A1-E053-46E4-8A51-6803638AF06D}</productID>
					<productID>{CDB47FFA-0760-4888-A5D2-54CDA3C8C29E}</productID>
					<productID>{E8B35E60-6DAB-4C72-99D3-6ABE148C089D}</productID>
					<productID>{ED664E5A-6D28-48EA-A2EE-B6356EF01B37}</productID>
					<productID>{EFC648C5-F3BC-4096-9AFE-23121EF06828}</productID>
					<productID>{F5A1B01A-5DA0-4E01-9DCD-263BD60B09A6}</productID>
					<productID>{F7BFA33C-DF4A-477C-82BB-E00827A03654}</productID>
					<productID>{F8018104-6294-4896-A9E2-CBC919992310}</productID>
					<productID>{FA85DBC5-063E-4CA0-9E3A-7C1180D8F7AE}</productID>
					<productID>{FB7B16DB-F395-4D41-A557-80386E0D771E}</productID>
					<productID>{FEC6BAA0-CCCC-485B-ABFA-4A349FC25C45}</productID>
					<productID>{FEFD819E-523F-4919-8151-9F7B5DE999AB}</productID>
					<productID>{FF4257C4-CB02-4A5F-9B09-D7FB822E53C2}</productID></dependencies></product>
			<product name="NI LabWindows/CVI Shared Runtime 2019" UC="{80D3D303-75B9-4607-9312-E5FC68E5BFD2}" productID="{2EB63900-C920-494E-9F7B-56E6B2DCBEE9}" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="19.0.49152">
				<dependencies>
					<productID>{0946CDFA-C3C6-4AD5-B884-FB72701ED351}</productID>
					<productID>{14B23AC5-B7EF-47D1-A57D-8666BAEE13C3}</productID>
					<productID>{16BC0547-DF57-48CF-8CB5-1CC0DF3B4911}</productID>
					<productID>{52981014-740C-430E-A83A-711186DF565B}</productID>
					<productID>{5B4D362F-8203-490C-82D1-5F607972196F}</productID>
					<productID>{60684600-163F-45D7-83DB-E247FA48D81F}</productID>
					<productID>{64ECB814-3A6A-4E48-9D2F-D6C2EDD725B7}</productID>
					<productID>{69181DFA-D7CA-4AFE-98E2-A985F32B557B}</productID>
					<productID>{6E1BCD5B-41A1-4E69-8C6E-389F57A19F00}</productID>
					<productID>{75191165-D39E-42A2-A7A2-D74AE99F8A84}</productID>
					<productID>{7EE28BBA-8A24-40B1-B0D0-9066A8CFA4AA}</productID>
					<productID>{81710CDC-7B4D-4A91-8D44-8E2F8B5C2B6E}</productID>
					<productID>{820FB6E8-8856-48D7-934C-76169DCCFD48}</productID>
					<productID>{88104A0D-1729-4A73-B798-80BEFC243F18}</productID>
					<productID>{88DFF01E-7C87-4E35-B194-CB7A2E32FA6D}</productID>
					<productID>{93977567-FFEC-453C-A47F-CE30077E9F4B}</productID>
					<productID>{9B14BAA8-31A5-463B-88C8-EC81F67BEE57}</productID>
					<productID>{AFC999BB-F270-46EF-B748-AE755EC75322}</productID>
					<productID>{B0049D5A-380E-4219-A69D-02273F86891C}</productID>
					<productID>{B29007A1-E053-46E4-8A51-6803638AF06D}</productID>
					<productID>{C0A9F5E2-DCD5-44C1-8B03-C560F4C06D6C}</productID>
					<productID>{CE61F080-FB64-4F6C-9763-A3060A0E59E6}</productID>
					<productID>{D1027BA0-C959-44E2-B4FA-10386404AF75}</productID>
					<productID>{D72C00A8-14F3-4E45-AFAC-5A71F833E210}</productID>
					<productID>{E12F09FF-07B3-4677-8D5C-BDD01E9A5545}</productID>
					<productID>{ED664E5A-6D28-48EA-A2EE-B6356EF01B37}</productID>
					<productID>{EEA5281C-7DA9-492E-8F6F-4127DC67AAD6}</productID>
					<productID>{EFC648C5-F3BC-4096-9AFE-23121EF06828}</productID>
					<productID>{F2EEE63A-0DCA-41BF-A243-4E4C0DFA38A4}</productID>
					<productID>{F456DB40-F5DF-45FE-A582-83DBED5D6432}</productID>
					<productID>{F8018104-6294-4896-A9E2-CBC919992310}</productID>
					<productID>{FA85DBC5-063E-4CA0-9E3A-7C1180D8F7AE}</productID>
					<productID>{FAFB3CD7-F8A6-4D31-BCB4-57354C17128E}</productID>
					<productID>{FB67912C-BB8D-4FE2-B64E-7712EB90DEA4}</productID></dependencies></product></baselineProducts>
		<Projects NumProjects="1">
			<Project000 ProjectID="0" ProjectAbsolutePath="f:\EWD-EOMS\EWD-EOMS\EOMS\EOMS.prj" ProjectRelativePath="EOMS.prj"/></Projects>
		<buildData progressBarRate="0.835628529843756">
			<progressTimes>
				<Begin>0.000000000000000</Begin>
				<ProductsAdded>1.788566937500000</ProductsAdded>
				<DPConfigured>2.683911343750000</DPConfigured>
				<DPMergeModulesAdded>3.501741437500000</DPMergeModulesAdded>
				<DPClosed>6.406149343749998</DPClosed>
				<DistributionsCopied>7.145114937499998</DistributionsCopied>
				<End>119.670399500000002</End></progressTimes></buildData>
	</msi>
</distribution>
