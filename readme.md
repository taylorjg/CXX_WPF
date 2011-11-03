# Exploration of C++ and WPF Integration

The idea of this project is to take a simple Visual C++ 6 MFC application as a starting point and then merge in some WPF / C# elements.

So initially I have the following projects:

- A Visual C++ 6 MFC Extension DLL that exposes a small subset of the entities provided by the wine.com OData service
- A Visual C++ 6 MFC Dialog-based application that displays some basic product information in an owner-drawn CListBox

The next steps will be:

- Migrate the above projects to Visual Studio 2010
- Create a new C++/CLI project to act as a thin layer over the MFC Extension DLL to make the native C++ classes available to managed code i.e. C#
- Try to replace the owner-drawn CListBox control with a WPF / C# component of some sort

## References:

- http://wine.com
- http://api.wine.com
- http://wine.cloudapp.net
- http://wine.cloudapp.net/$metadata
- http://www.odata.org/
- http://www.amazon.co.uk/CLI-Action-Manning-Nishant-Sivakumar/dp/1932394818
- http://www.amazon.co.uk/Expert-CLI-Visual-Programmers-Experts/dp/1590597567
