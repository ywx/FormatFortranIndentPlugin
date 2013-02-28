Format Fortran Indent Plugin
----------------------------
A Code::Blocks Plugin to Format Source Code Indent for Fortran 95, Fortran 90 Source Code (free source form).

NOTE: It could not completely support "type", "function", "subroutine" statement. It could not support nonblock-do-construct. There are some known bugs in "if", "for", "forall", "where" statement in some cases.


Author:    YWX (wxFortranIndent@163.com)
Created:   2011-12-22
Copyright: (c) YWX <wxFortranIndent@163.com>
License:   GNU General Public License, version 3

Artistic Style Plugin ( v2.02, May 2011 ) in Code::Blocks could not format the indent correctly for Fortran Source Code. Format Fortran Indent Plugin was created in December 25th 2011. Compared with Artistic Style Plugin, it is a small attempt. Although there are some unexpected bugs in it, it is able to run on Code::Blocks for Windows. It is tested on Windows platform only. The configured settings for linux platform is offered by Darius Markauskas<darmar.lt@gmail.com>.

Send bug reports and questions to YWX <wxFortranIndent@163.com>.

Please notice that often trying to correct the bug yourself is the
quickest way to fix it. Even if you fail to do it, you may
discover valuable information allowing us to fix it while doing
it. We also give much higher priority to bug reports with patches
fixing the problems so this ensures that your report will be
addressed sooner.

To get the source code, please visit https://github.com/ywx/FormatFortranIndentPlugin
Get a local copy of the Format Fortran Indent Plugin repository with this command:
git clone git://github.com/ywx/FormatFortranIndentPlugin.git FormatFortranIndentPlugin-ReadOnly

For information on Git，please see http://git-scm.com/ or https://github.com/git/git
For information on Git for Windows，please see http://code.google.com/p/msysgit/
For information on TortoiseGit，please see http://code.google.com/p/tortoisegit/

Format_Fortran_Indent_Plugin.cbplugin in repository is compiled by MinGW TDM-GCC with  wxWidgets and Code::Blocks SDK. cbRelease branch is built for Code::Blocks Release. cbFortran branch is built for Code::Blocks IDE for Fortran. Keep source code for project only in master branch.

Compilers and Options ( for Windows )
=====================================
1, For windows, MinGW complier is preferred, combined with Code::Blocks.
2, Please download wxWidgets source code, to produce the single dynamic link library SDK.
3, Please download Code::Blocks Fortran or Code::Blocks source code, to produce Code::Blocks SDK and Code::Blocks with SDK in step 2.
4, Please download Format Fortran Indent Plugin source code, to be compiled in Code::Blocks with SDK from step 2 and 3.

For information on MinGW, please see http://www.mingw.org
For information on MinGW TDM-GCC, please see http://tdm-gcc.tdragon.net
For information on wxWidgets, please see http://www.wxwidgets.org
For information on Code::Blocks, please see http://www.codeblocks.org
For information on Code::Blocks Plug-In development, please see http://wiki.codeblocks.org/index.php?title=Developer_documentation
For information on Code::Blocks IDE for Fortran, please see http://darmar.vgtu.lt/ or http://code.google.com/p/fortranproject/


Last updated: February 13th 2013




Format Fortran Indent Plugin
----------------------------
一个用于将 Fortran 95, Fortran 90 自由格式源文件，进行代码缩进格式化的 Code::Blocks 插件。

注意：目前它还不能完美支持 type, function, subroutine 等语句。它也不能支持 nonblock-do-construct 。在对 if, for, forall, where 语句的支持中存在已知的可能发生的错误（但错误出现的概率较小）。

作者:    YWX (wxFortranIndent@163.com)
创建于:  2011-12-22
Copyright: (c) YWX <wxFortranIndent@163.com>
License:   GNU General Public License, version 3

由于 Code::Blocks 里面的 Artistic Style Plugin ( v2.02, May 2011 ) 不能对 Fortran 源代码进行正确的代码缩进格式化。所以 Format Fortran Indent Plugin 诞生于 2011-12-25。相对于 Artistic Style Plugin 来说，它只是一个小玩意儿。尽管还有许多不可预见的Bug。但令我们高兴的是，它能在 Windows 版的 Code::Blocks 上工作。它只在 Windows 平台上运行测试过。Linux版的编译配置是由 Darius Markauskas<darmar.lt@gmail.com> 提供。在此表示感谢。

有 Bug 和使用问题，请发送邮件到 YWX <wxFortranIndent@163.com>。

插件的源代码仓库托管在 https://github.com/ywx/FormatFortranIndentPlugin
你可以用以下命令得到代码仓库的一份只读克隆。
git clone git://github.com/ywx/FormatFortranIndentPlugin.git FormatFortranIndentPlugin-ReadOnly

关于 Git，请访问 http://git-scm.com/ 或 https://github.com/git/git
关于 Git for Windows，请访问 http://code.google.com/p/msysgit/
关于 TortoiseGit，请访问 http://code.google.com/p/tortoisegit/

仓库上的 Format_Fortran_Indent_Plugin.cbplugin 基于 wxWidgets 和 Code::Blocks SDK 由 MinGW TDM-GCC 编译生成。cbRelease 分支适用于 Code::Blocks Release 版本。cbFortran 分支适用于 Code::Blocks IDE for Fortran 版本。master 分支只保留用于项目构建的源代码。

编译插件（在Windows下）：
========================
1，Windows 最好请用 MinGW 编译器和 Code::Blocks 集成开发环境。
2，请下载 wxWidgets 源代码，编译生成单一的动态链接库SDK。
3，请下载 Code::Blocks Fortran 或 Code::Blocks 源代码，用步骤2生成的动态链接库SDK编译生成 Code::Blocks SDK 和 Code::Blocks。
4，请从上述代码仓库上下载 Format Fortran Indent Plugin 源代码。用步骤2和3生成的SDK在 Code::Blocks 编译。

关于 MinGW32，请访问 http://www.mingw.org
关于 MinGW TDM-GCC，请访问 http://tdm-gcc.tdragon.net
关于 wxWidgets，请访问 http://www.wxwidgets.org
关于 Code::Blocks，请访问 http://www.codeblocks.org
关于 Code::Blocks Plug-In 开发，请访问  http://wiki.codeblocks.org/index.php?title=Developer_documentation
关于 Code::Blocks IDE for Fortran，请访问 http://darmar.vgtu.lt/ 或 http://code.google.com/p/fortranproject/

Format Fortran Indent Plugin 只是运用正则表达式对源代码进行以行为单位的模式匹配，然后进行代码缩进格式化。所以它只能支持Fortran 95, Fortran 90语法中的一个子集。目前它还不能完美支持 type, function, subroutine 等语句，也不能支持 nonblock-do-construct 。有空的话，我会完善它。希望大家也来关心它，培养它。更希望有人能从编译原理方向重塑它。


最后更新: 2013-2-13
