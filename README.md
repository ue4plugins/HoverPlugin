# HoverPlugin

Unreal Engine 4 plug-in with hover effect components.


## About

This Unreal Engine 4 plug-in shows how to convert a BP component to a C++
component as presented by Zak Parrish and Gerke Max Preussner during the
live coding demonstration at GDCE Europe 2015. It accompanies the corresponding
[presentation slides](https://headcrash.industries/vault/presentations/gdc-europe/)


## Supported Platforms

This plug-in was last built against **Unreal Engine 4.17** and works on all
platforms.


## Dependencies

This plug-in requires Visual Studio and either a C++ code project or a the full
Unreal Engine 4 source code from GitHub. If you are new to programming in UE4,
please see the official [Programming Guide](https://docs.unrealengine.com/latest/INT/Programming/index.html)!


## Usage

You can use this plug-in as a project plug-in, or an Engine plug-in.

If you use it as a project plug-in, clone this repository into your project's
*/Plugins* directory and compile your game in Visual Studio. A C++ code project
is required for this to work.

If you use it as an Engine plug-in, clone this repository into the
*/Engine/Plugins/Media* directory and compile your game. Full Unreal Engine 4
source code from GitHub (4.9 or higher) is required for this.

After compiling the plug-in, you have to **enable it** in Unreal Editor's plug-in
browser.

In order to use the Blueprint version of the hover component, copy the file
*/Content/BlueprintHoverComponent.uasset* into your project's */Content* directory.

Perform the following steps to test the components:

1. Drag a *Sphere* from the *Basic Shapes* tab into your level
2. Select the actor, lift it off the floor a bit, and click the *Add Component* button in the *Details* panel
3. Add the desired hover component, i.e. *SimpleHoverComponent* or *BlueprintHoverComponent*
4. Make sure the *Mobility* of the actor's StaticMeshComponent is set to *Movable*
5. Hit the *Play* button to start the game in the Editor

Your sphere should now be hovering above the floor, slowly bouncing up and down into
a stable position.

Please note that the *HoverForce* value in the *SimpleHoverComponent* depends on
the mass of the static mesh actor, and its default value has been adjusted to
match the mass of a Sphere actor, which is currently 109.456337 kg. If you use
*SimpleHoverComponent* with a mesh other than the default Sphere then you have
to set its HoverForce to: *HoverForce = Mass * 10000.0* instead, or otherwise
the physics won't match those of *AsyncHoverComponent* if you compare the two.


## Support

Please [file an issue](https://github.com/ue4plugins/HoverPlugin/issues), submit a
[pull request](https://github.com/ue4plugins/HoverPlugin/pulls?q=is%3Aopen+is%3Apr)
or email us at info@headcrash.industries


## References

* [GDCE 2015: Blueprint Components to C++](https://forums.unrealengine.com/showthread.php?81573-GDCE-2015-Blueprint-Components-to-C)
* [Introduction to UE4 Plugins](https://wiki.unrealengine.com/An_Introduction_to_UE4_Plugins)
