################################
# Licensing                    #
################################

KSC Email Tracker is licensed under the GPL 3.0. KSC Email Tracker is also made possible by various other software:

* LIEL - Language Independent Extension Library (by Petroules Enterprises)
	Licensed under the standard LGPL 2.1
* Qt 4.6 (by Nokia)
	Licensed under the standard LGPL 2.1 with an exception
* A modified version of QtSingleApplication 2.6 (by Nokia)
	Licensed under the standard LGPL 2.1 with an exception
* create-dmg 1.0.0.2 (by YourSway)
	Licensed under the GPL
	Note that this tool is only used as part of our build process, it is not *incorporated* into our software and thus does not require we license KSC Email Tracker under the GPL
	Home page at: http://www.yoursway.com/free/#createdmg

Licenses for all of these products can be found in res/license.

################################
# Build Instructions           #
################################

Prerequisites:
* Qt 4.6
* Qt Creator 2.0

Download the latest KSC Email Tracker source code from http://www.petroules.com/products/kscemailtracker/

Extract the zip folder; your folder structure should now look like this:

3rdparty
	qtsingleapplication
liel
petroules
kscemailtracker

Navigate to the qtsingleapplication folder and open a terminal/command prompt. Enter:

(For Unix)

chmod +x configure
./configure -library

(For Windows)

configure.bat -library

You will be prompted to accept qtsingleapplication's license (you should choose LGPL). Follow the on-screen instructions - note that if you do not accept the terms of qtsingleapplication's license agreement you cannot continue beyond this point to build Silverlock.

Using Qt Creator, build qtsingleapplication, and LIEL, then KSC Email Tracker.

To build the installers, run deploy/win32/deploy.bat for Windows and deploy/macx/deploy.sh for Mac OS X. Installers for Linux are not currently available.