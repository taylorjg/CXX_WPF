# Exploration of C++ and WPF Integration

The idea of this project was to take a simple Visual C++ 6 MFC application as a starting point and then merge in
some WPF / C# elements.

So initially I started with the following projects:

- VS6/WineService
    - A Visual C++ 6 MFC Extension DLL that exposes a small subset of the
                 entities provided by the wine.com OData service.
- VS6/WineDemo
    - A Visual C++ 6 MFC Dialog-based application that displays some basic
                 product information in an owner-drawn CListBox.

I then migrated these projects to Visual Studio 2010.

I then added 3 new projects by following these sections in the book "C++/CLI in Action":

- 5.4 Exposing an MFC extension DLL to .NET
- 7.4 Hosting a WPF control in a native C++ application

This resulted in the following list of projects:

- VS2010/WineService
    - Migrated MFC Extension DLL. Still native VC++.
- VS2010/WineDemo
    - Migrated MFC Dialog-based application. Still native VC++.
- VS2010/WineServiceShim
    - MFC Regular DLL built with /clr. Exposes managed reference types to C#.
- VS2010/WineDemoUserControls
    - WPF User Control Library (C#). Houses a user control called WineList that contains a ListView control.
This user control replaces the owner-drawn CListBox in the original MFC application.
It data binds to the managed types exposed by the WineServiceShim project.
- VS2010/WineDemoUserControlsWrapper
    - MFC Extension DLL built with /clr. Wraps the WPF WineList user control by hosting it in a `HwndSource`.

### Issues - Resolved

- VC++ project settings for General | Character Set
    - Need to ensure that all the VC++ projects in the solution use the same value for this setting
otherwise I got various nasty problems. I am using the value "Use Multi-Byte Character Set" for all projects.
- error C3767: 'Product::Product': candidate function(s) not accessible, etc.
    - Needed to use #pragma make_public in WineService.h to resolve these errors

### Issues - Unresolved

- #include via a shortcut
    - I have a shortcut in the lib subdirectory that links to the location
of the boost libraries on my machine. In VS6, I can use this shortcut as an additional include directory
i.e. "..\lib\boost_1_47_0". However, VS2010 doesn't seem to follow the shortcut.
- Design-time data (WineList.xaml)
    - I have tried to include some design-time data in my WineListViewModel class
but it doesn't show up in the Visual Studio designer.

### References:

- http://wine.com
- http://api.wine.com
- http://wine.cloudapp.net
- http://wine.cloudapp.net/$metadata
- http://www.odata.org/
- http://www.amazon.co.uk/CLI-Action-Manning-Nishant-Sivakumar/dp/1932394818
- http://www.amazon.co.uk/Expert-CLI-Visual-Programmers-Experts/dp/1590597567
