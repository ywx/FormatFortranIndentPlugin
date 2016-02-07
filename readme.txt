Format Fortran Indent Plugin
----------------------------
A Code::Blocks Plugin to Format Source Code Indent for Fortran 95, Fortran 90 Free Format Source Code.

NOTE: It could not work on Fortran Fixed Format Source Code. It could not completely support "type", "function", "subroutine" statement. It could not support nonblock-do-construct. There are some known bugs in "if", "for", "forall", "where" statement in some cases.


Author:    YWX (wxFortranIndent@163.com)
Created:   2011-12-22
Copyright: (c) YWX <wxFortranIndent@163.com>
License:   GNU General Public License, version 3

Artistic Style Plugin ( v2.02, May 2011 ) in Code::Blocks could not format the indent correctly for Fortran Source Code. Format Fortran Indent Plugin was created in December 25th 2011. Compared with Artistic Style Plugin, it is a small attempt. Although there are some unexpected bugs in it, it is able to run on Code::Blocks for Windows. It is tested on Windows platform only. The old configured settings for Linux platform is offered by Darius Markauskas<darmar.lt@gmail.com>.

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
For information on Git for Windows，please see https://git-for-windows.github.io

Keep source code for project only in master branch. Download prebuilt FormatFortranIndentPlugin.cbplugin from https://github.com/ywx/FormatFortranIndentPlugin/releases . 

How to Use the Format Fortran Indent Plugin for Code::Blocks ?
Please see https://github.com/ywx/FormatFortranIndentPlugin/wiki/HowtoUse-zh
How to change options for Format Fortran Indent Plugin ?
Please see https://github.com/ywx/FormatFortranIndentPlugin/wiki/HowtoChangeOptions-zh


Compilers and Options ( for Windows )
=====================================
1, For windows, MinGW complier is preferred, combined with Code::Blocks.
2, Please download wxWidgets source code, to produce the single dynamic link library SDK.
3, Please download Code::Blocks source code, to produce Code::Blocks SDK with the wxWidgets SDK in step 2.
4, Please download Format Fortran Indent Plugin source code, open FormatFortranIndentPlugin.cbp to build with Code::Blocks and wxWidgets SDK in step 2 and 3 under "Win32 Release" or "Win32 Debug" Build targer.

For information on MinGW, please see http://www.mingw.org
For information on MinGW TDM-GCC, please see http://tdm-gcc.tdragon.net
For information on wxWidgets, please see http://www.wxwidgets.org
For information on Code::Blocks, please see http://www.codeblocks.org
For information on Code::Blocks Plug-In development, please see http://wiki.codeblocks.org/index.php?title=Developer_documentation
For information on Code::Blocks IDE for Fortran, please see http://darmar.vgtu.lt/ or http://code.google.com/p/fortranproject/
For information on Code::Blocks Nightly Build, please see http://forums.codeblocks.org/index.php?board=20.0 and http://forums.codeblocks.org/index.php/topic,3232.0.html ( How to use a nightly build )


Compilers and Options ( for Linux )
=====================================
1, Install wxBase, wxGTK and xterm for Code::Blocks.
2, Please download Code::Blocks for Linux, to set up develop IDE.
3, Install gcc-g++, wxGTK-devel, codeblocks-devel and codeblocks-contrib-devel to build Code::Blocks Plugin.
4, Please download Format Fortran Indent Plugin source code, open FormatFortranIndentPlugin-unix.cbp to build in Code::Blocks under "Unix Release" or "Unix Debug" Build targer.

For information on Fedora, please see http://www.fedoraproject.org
For information on Deian, please see http://www.debian.org
For information on gcc, please see http://gcc.gnu.org
For information on wxWidgets, please see http://www.wxwidgets.org
For information on Code::Blocks, please see http://www.codeblocks.org
For information on Code::Blocks Plug-In development, please see http://wiki.codeblocks.org/index.php?title=Developer_documentation
For information on Code::Blocks IDE for Fortran, please see http://darmar.vgtu.lt/ or http://sourceforge.net/projects/fortranproject/


Last updated: February 6th 2016




Format Fortran Indent Plugin
----------------------------
一个用于将 Fortran 95, Fortran 90 Free Format 源码，进行代码缩进格式化的 Code::Blocks 插件。

注意：不支持 Fixed Format Fortran 源码。目前它还不能完美支持 type, function, subroutine 等语句。它也不能支持 nonblock-do-construct 。在对 if, for, forall, where 语句的支持中存在已知的可能发生的错误（但错误出现的概率较小）。

作者:    YWX (wxFortranIndent@163.com)
创建于:  2011-12-22
Copyright: (c) YWX <wxFortranIndent@163.com>
License:   GNU General Public License, version 3

由于 Code::Blocks 里面的 Artistic Style Plugin ( v2.02, May 2011 ) 不能对 Fortran 源代码进行正确的代码缩进格式化。所以 Format Fortran Indent Plugin 诞生于 2011-12-25。相对于 Artistic Style Plugin 来说，它只是一个小玩意儿。尽管还有许多不可预见的Bug。但令我们高兴的是，它能在 Windows 版的 Code::Blocks 上工作。它只在 Windows 平台上运行测试过。先前Linux版的编译配置是由 Darius Markauskas<darmar.lt@gmail.com> 提供。在此表示感谢。

有 Bug 和使用问题，请发送邮件到 YWX <wxFortranIndent@163.com>。

插件的源代码仓库托管在 https://github.com/ywx/FormatFortranIndentPlugin
你可以用以下命令得到代码仓库的一份只读拷贝。
git clone git://github.com/ywx/FormatFortranIndentPlugin.git FormatFortranIndentPlugin-ReadOnly

关于 Git，请访问 http://git-scm.com/ 或 https://github.com/git/git
关于 Git for Windows，请访问 https://git-for-windows.github.io

仓库 master 分支只保留用于项目构建的源代码。预编译的 FormatFortranIndentPlugin.cbplugin 可从 https://github.com/ywx/FormatFortranIndentPlugin/releases 下载。

How to Use the Format Fortran Indent Plugin for Code::Blocks ?
请访问 https://github.com/ywx/FormatFortranIndentPlugin/wiki/HowtoUse-zh
How to change options for Format Fortran Indent Plugin ?
请访问 https://github.com/ywx/FormatFortranIndentPlugin/wiki/HowtoChangeOptions-zh


编译插件（在 Windows 下）：
========================
1，Windows 最好请用 MinGW 编译器和 Code::Blocks 集成开发环境。
2，请下载 wxWidgets 源代码，编译生成单一的动态链接库的 wxWidgets SDK。
3，请下载 Code::Blocks 源代码，用步骤2生成的 wxWidgets SDK 编译生成 Code::Blocks SDK。
4，请从上述代码仓库上下载 Format Fortran Indent Plugin 源代码。用步骤2和3生成的 wxWidgets 和 Code::Blocks SDK在 Code::Blocks 使用 "Win32 Release" 或 "Win32 Debug" Build targer 编译。

关于 MinGW32，请访问 http://www.mingw.org
关于 MinGW TDM-GCC，请访问 http://tdm-gcc.tdragon.net
关于 wxWidgets，请访问 http://www.wxwidgets.org
关于 Code::Blocks，请访问 http://www.codeblocks.org
关于 Code::Blocks Plug-In 开发，请访问  http://wiki.codeblocks.org/index.php?title=Developer_documentation
关于 Code::Blocks IDE for Fortran，请访问 http://darmar.vgtu.lt/ 或 http://sourceforge.net/projects/fortranproject/
关于 Code::Blocks Nightly Build，请访问 http://forums.codeblocks.org/index.php?board=20.0 和 http://forums.codeblocks.org/index.php/topic,3232.0.html ( How to use a nightly build )

编译插件（在 Linux 下）
=====================================
1, 安装 Code::Blocks 前，先安装相应 wxBase 和 wxGTK 运行包 及 xterm 。
2, 下载相应 Code::Blocks for Linux 并安装，构建开发 IDE。
3, 安装 gcc-g++, wxGTK-devel, codeblocks-devel 和 codeblocks-contrib-devel 开发包，用于编译 Code::Blocks Plugin。
4, 请从上述代码仓库下载 Format Fortran Indent Plugin 源代码。用 Code::Blocks 在 "Unix Release" 或 "Unix Debug" Build targer 下编译。

关于 Fedora，请访问 see http://www.fedoraproject.org
关于 Deian，请访问 see http://www.debian.org
关于 gcc，请访问 http://gcc.gnu.org
关于 wxWidgets，请访问 http://www.wxwidgets.org
关于 Code::Blocks，请访问 http://www.codeblocks.org
关于 Code::Blocks Plug-In development，请访问 http://wiki.codeblocks.org/index.php?title=Developer_documentation
关于 Code::Blocks IDE for Fortran，请访问 http://darmar.vgtu.lt/ or http://code.google.com/p/fortranproject/


Format Fortran Indent Plugin 只是运用正则表达式对源代码进行以行为单位的模式匹配，然后进行代码缩进格式化。所以它只能支持Fortran 95, Fortran 90语法中的一个子集。目前它还不能完美支持 type, function, subroutine 等语句，也不能支持 nonblock-do-construct 。有空的话，我会完善它。希望大家也来关心它，培养它。更希望有人能从编译原理方向重塑它。


最后更新: 2016-2-6
