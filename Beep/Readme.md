#Mncl::Beep class
Mncl::Beep controls PC lagacy beep. 

#Methods
##Beep( dwFreq ,dwDuration )
It is a most majer feature in this class.
Generates simple tones on the speaker. The function is synchronous;
it performs an alertable wait and does not return control to its caller until the sound finishes.

    Mncl::Beep( 440 ,300 );

##On( )
Generates simple tones on the speaker continuous.

##Off( )
Stop tones the speaker.

##SetFrequency( wFreq )
This method doesn't touch speaker. Just changes frequency settings.
If the 'On( )' method was already called then the tones should be change the new frequency tones.


