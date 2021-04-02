# Feedback on proposal

## How do you plan on tackling the project?

### ad Week 1. 
Yes there is more malware on Windows, but to demonstrate the concept Linux would work equally well and is very likely easier to do.

Please create a deliverable (as a readable report in the git repo) for Week 1 that explains in much detail how your chosen target system resolves DNS names. What are the programs/services involved, how do they communicate with each other, etc. This is the background information you need to gather before you can start the project in earnest. Any lack in knowledge here will impede the project going forward.

### ad Week 2.
"Figure out how to block program network traffic with our own program running as administrator
and piece. Automate system to determine IP vs DNS request."

What did you want to say at: "and piece."?

"Automate system to determine IP vs DNS request" becomes trivial if you do your homework for Week 1.

Essentially, Week 2 is "only" coming up with a design based on the knowledge gained in Week 1. (i.e., not worth a week of work). You should be more ambitious here.

### ad Week 3.

I'd suggest you do what you have proposed in Week 3, in Week 2 instead.

### ad Week 4.

"Keep working on week 3 work if necessary"

Some buffer is good, but given we just compacted Weeks 2 & 3 into one week, this should not be necessary.

"as well collect malware that will be statically analyzed to determine if it actually attempts to connect to an IP directly (or by examining source code from a malware using in other epochs) for use in a demo"

While you can test your implementation with real malware, I'd get started with demo programs that you created yourself. Write two simple C programs, one that connects to a website via it's ip address and the other uses the site's domain name. Subsequently, you can start looking for malware. Studying VirusTotal or other repositories that give you the information whether a sample talks DNS or not and what IPs are connected could be helpful.

"In addition if other work has been completed, create other features such as
notifying the user and logging data."

Possible, but somewhat tangential. I'd imagine that by Week 2 you have a prototype, so another task could be developing something that works reliably (i.e., not just a prototype). Again that relies on the understanding you built in Week 1 on how networking and DNS work in the operating system you're choosing to develop for.

## What's the demo going to be?
