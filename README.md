PMC-Conductor
==================

这是一款实时数据库系统，包括三个部分，实时数据库、组态软件、控制器逻辑程序。

实时数据库位于pmc目录中，主要是使用MFC编写，用来对控制器的数据进行实时存储和操作。

组态软件位于conductor/app目录中，主要包括conductor组态软件(Delphi语言编写)，f8uuid这个UUID模块，fcc功能块执行程序。

控制器逻辑程序位于conductor/vxWorks中，包括控制器内核f8kernel，使用vxWorks平台可以将这个逻辑程序下载到控制器中进行运行。
