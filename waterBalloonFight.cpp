/*-------------------------------------------------------------------------*
 *---									---*
 *---		waterBalloonFight.cpp					---*
 *---									---*
 *---	    This file defines a program the simulates the throwing and	---*
 *---	catching of waterballoons to demonstrate linked list and multi-	---*
 *---	threaded programming.						---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2022 February 8		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

//	Compile with:
//	$ g++ waterBalloonFight.cpp -o waterBalloonFight -lpthread -g

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<pthread.h>
#include	<unistd.h>	// For sleep()

//  PURPOSE:  To hold the names of the water balloon throwers.
const char*	NAME_CPTR_ARRAY	[]	= {"Alice",
      					   "Bob",
					   "Cathy",
					   "David"
					  };

//  PURPOSE:  To tell the number of water balloon throwers.
const int	NUM_BALLOON_THROWERS	= sizeof(NAME_CPTR_ARRAY) /
					  sizeof(const char*);

class		BalloonThrower;

extern
void*		throwing	(void*	vPtr
				);


//  PURPOSE:  To hold the address of each water balloon thrower.
BalloonThrower*	throwerPtrArray[NUM_BALLOON_THROWERS];

//  PURPOSE:  To hold the specification for non-blocking threads.
//  YOUR CODE HERE
pthread_attr_t tAttr;
pthread_mutex_t lock;

//  PURPOSE:  To hold 'true' while the fight is still on, or 'false'
//	after the fight is over.
bool		isTimeOver		= false;

//  PURPOSE:  To keep track of the number of water balloons that have not
//	yet been destroyed.
int		globalNumBalloons	= NUM_BALLOON_THROWERS;

//  PURPOSE:  To protect access to 'globalNumBalloons'.
//  YOUR CODE HERE
pthread_mutex_t lock_;


//  PURPOSE:  To return 'true' when the throwers should stop throwing, or
//	'false' otherwise.
bool		getShouldStillFight	()
{
  return( !isTimeOver && (globalNumBalloons > 0) );
}


//  PURPOSE:  To safely decrement 'globalNumBalloons'.  No parameters.
//	No return value.
void	   	decrementGlobalNumBalloons
					()
{
  //  YOUR CODE HERE
  pthread_mutex_lock(&lock);
}


//  PURPOSE:  To represent one throwing of a water balloon at another
//	BalloonThrower instance.
class		Throwing
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the address of the target.
  BalloonThrower*		targetPtr_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  Throwing			();

  //  No copy constructor:
  Throwing			(const Throwing&);

  //  No copy assignment op:
  Throwing&	operator=	(const Throwing&);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to note that '*newTargetPtr' has a
  //	water balloon thrown at them.  No return value.
  Throwing			(BalloonThrower*	newTargetPtr
  				) :
				targetPtr_(newTargetPtr)
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~Throwing			()
				{ }

  //  V.  Accessor(s):
  //  PURPOSE:  To return the address of the target.  No parameters.
  BalloonThrower*
		getTargetPtr	()
				const
				{ return(targetPtr_); }

  //  VI.  Mutator(s):

  //  VII.  Method(s) that do main and misc. work of class.
  //  PURPOSE:  To have '*this' Thowing spend time flying thru the air before
  //	arriving at the target from them to attempt to catch.  No parameters.
  //	No return value.
  void		fly		();

};


class		BalloonThrower
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the index of the name of '*this' BalloonThrower
  //	instance. 
  int				nameIndex_;

  //  PURPOSE:  To hold 'true' if the thrower is about to throw or 'false'
  //	otherwise.
  bool				isAboutToThrow_;

  //  PURPOSE:  To tell the current number of balloons.
  int				numBalloons_;

  //  PURPOSE:  To tell the number of times '*this' person was hit.
  int				numTimesHit_;

  //  PURPOSE:  To lock '*this' BalloonThrower instance.
  //  YOUR CODE HERE
  pthread_mutex_t lock_;

  //  PURPOSE:  To be signaled when have a balloon to throw.
  //  YOUR CODE HERE
  pthread_cond_t throwSig_;
  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  BalloonThrower		();

  //  No copy constructor:
  BalloonThrower		(const BalloonThrower&);

  //  No copy assignment op:
  BalloonThrower&
		operator=	(const BalloonThrower&);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to be the 'i'-th balloon thrower.
  //	No return value.
  BalloonThrower		(int	i
				) :
				nameIndex_(i),
				isAboutToThrow_(false),
				numBalloons_(1),
				numTimesHit_(0)
				{
				  //  YOUR CODE HERE
				  pthread_mutex_init(&lock_, NULL);
				  pthread_cond_init(&throwSig_,NULL);
				}

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No
  //	return value.
  ~BalloonThrower		()
  				{
				  //  YOUR CODE HERE
				  pthread_mutex_destroy(&lock_);
				  pthread_cond_destroy(&throwSig_);
				}

  //  V.  Accessors:
  //  PURPOSE:  To return the index of the name of '*this' BalloonThrower
  //	instance.  No parameters.
  int		getNameIndex	()
				const
				{ return(nameIndex_); }

  //  PURPOSE:  To hold the address of the name of the thrower.
  const char*	getNameCPtr	()
				const
				{ return(NAME_CPTR_ARRAY[getNameIndex()]); }

  //  PURPOSE:  To hold 'true' if the thrower is about to throw or 'false'
  //	otherwise.
  bool		getIsAboutToThrow
				()
				const
				{ return(isAboutToThrow_); }

  //  PURPOSE:  To return 'true' if '*this' has at least one balloon or
  //	'false' otherwise.
  bool		haveBalloon	()
  				const
				{ return(numBalloons_ > 0); }

  //  PURPOSE:  To return the number of times '*this' person was hit.  No
  //	parameters.
  int		getNumTimesHit	()
				const
				{ return(numTimesHit_); }

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To set 'isAboutToThrow_' to 'true' after '*this' has a balloon
  //	to throw.  No parameters.  No return value.
  void		prepareToThrow	()
  {
    //  YOUR CODE HERE
	pthread_mutex_lock (&lock_);
	while(!haveBalloon()) 
	{
		pthread_cond_wait(&throwSig_, &lock_);
		if ( !getShouldStillFight() )
		{
			return;
		}
	}
    isAboutToThrow_	= true;
    printf
	("%s \"I have selected the perfect balloon for my next victim!\"\n",
	 getNameCPtr()
    	);
    //  YOUR CODE HERE
	pthread_mutex_unlock(&lock_);
  }


  //  PURPOSE:  To have '*this' throw thow a balloon at a random target
  //	(other than themself).  No parameters.  No return value.
  void		throwBalloon	()
  {
    //  I.  Application validity check:

    //  II.  Throw a water balloon:
    //  II.A.  Identity a target (other than self):
    int		targetIndex;

    do
    {
      targetIndex	= rand() % NUM_BALLOON_THROWERS;
    }
    while  (targetIndex == getNameIndex());

    printf
	("%s \"Hey %s, here it comes!\"\n",
	 getNameCPtr(),NAME_CPTR_ARRAY[targetIndex]
    	);

    //  II.B.  Identity a target (other than self):
    pthread_t	threadId;

    //  YOUR CODE HERE
	pthread_mutex_lock (&lock_);
	numBalloons_--;
	isAboutToThrow_	= false;
	pthread_create(&threadId, &tAttr, throwing, new Throwing(throwerPtrArray[targetIndex]));
	pthread_mutex_unlock(&lock_);

    //  III.  Finished:
  }


  //  PURPOSE:  To attempt to catch '*throwing'.  If '*this' thrower
  //  	was not about to throw then the catch of the balloon will be
  //	successful, and '*this' thrower will have one more balloon.
  //	However, if '*this' thrower was about to throw, then they will not
  //	get the balloon, increment 'numTimesHit_' (and _will_ get wet!)
  //	No return value.
  void		attemptToCatch	(Throwing*	throwing
  				)
  {
    //  YOUR CODE HERE
	pthread_mutex_lock(&lock_);

    if  (getIsAboutToThrow())
    {
      numTimesHit_++;
      printf("(Splash!)  %s \"Yuck!  I'm wet!\"\n",getNameCPtr());
      decrementGlobalNumBalloons();
    }
    else
    {
      numBalloons_++;
      printf
	("%s \"Thanks for the balloon!  "
	 "Now I have one more for my arsenal!\"\n",
      	 getNameCPtr()
	);
    }

    //  YOUR CODE HERE
	pthread_cond_signal(&throwSig_);
	pthread_mutex_unlock(&lock_);
  }

  //  PURPOSE:  To tell '*this' thread that the fight is over.  No parameters.
  //	No return value.
  void		informThatFightIsOver	()
  {
    //  YOUR CODE HERE
	pthread_cond_signal(&throwSig_);
  }

};


//  PURPOSE:  To have '*this' Thowing spend time flying thru the air befire
//	arriving at the target from them to attempt to catch.  No parameters.
//	No return value.
void		Throwing::fly		()
{
  sleep(1 + rand() % 10);
  getTargetPtr()->attemptToCatch(this);
}


void*		throwing	(void*	vPtr
				)
{
  //  YOUR CODE HERE
  Throwing* tempPtr =(Throwing*) vPtr;
  tempPtr->fly();
  return(NULL);
}


void*		balloonFight		(void*		vPtr
					)
{
  BalloonThrower*	throwerPtr	= (BalloonThrower*)vPtr;

  while  ( getShouldStillFight() )
  {
    sleep(rand() % 10 + 1);

    if  ( !getShouldStillFight() )
    {
      break;
    }

    throwerPtr->prepareToThrow();
    sleep(rand() % 2 + 1);

    if  ( !getShouldStillFight() )
    {
      break;
    }

    throwerPtr->throwBalloon();
  }

  if  (throwerPtr->getNumTimesHit() == 0)
  {
    printf
	("%s \"Hah!  The fight is over and I'm still dry!\"\n",
	 throwerPtr->getNameCPtr()
	);
  }
  else
  {
    printf("%s \"I will win next time!\"\n",throwerPtr->getNameCPtr());
  }

  return(NULL);
}


int		main		(int		argc,
				 char*		argv[]
				)
{
  //  I.  Application validity check:

  //  II.   Conduct water balloon fight:
  //  II.A.  Initialize random number generator:
  char*	     cPtr;
  int	     seed;

  if  ( (argc >= 2)  &&  (seed = strtol(argv[1],&cPtr,0), *cPtr == '\0') )
  {
    srand(seed);
  }
  else
  {
    srand(getpid());
  }

  //  II.B.  Initialize vars:
  //  YOUR CODE HERE
  pthread_attr_init (&tAttr);
  pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);

  for  (int i = 0;  i < NUM_BALLOON_THROWERS;  i++)
  {
    throwerPtrArray[i]	= new BalloonThrower(i);
  }

  sleep(1);

  //  II.C.  Conduct fight:
  pthread_t	throwerIdArray[NUM_BALLOON_THROWERS];

  printf("The fight begins!\n");

  for  (int i = 0;  i < NUM_BALLOON_THROWERS;  i++)
  {
    //  YOUR CODE HERE
	pthread_create(&throwerIdArray[i], NULL, balloonFight, throwerPtrArray[i]);
  }

  sleep(30);

  //  II.D.  Stop fight:
  printf("The fight is over!\n");
  isTimeOver	= true;

  for  (int i = 0;  i < NUM_BALLOON_THROWERS;  i++)
  {
    throwerPtrArray[i]->informThatFightIsOver();
    //  YOUR CODE HERE
	pthread_join(throwerIdArray[i], (void**)&seed);
  }

  //  II.E.  Clean up:
  sleep(10);

  for  (int i = 0;  i < NUM_BALLOON_THROWERS;  i++)
  {
    delete(throwerPtrArray[i]);
  }

  //  YOUR CODE HERE
  pthread_attr_init(&tAttr);
  pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
  pthread_mutex_destroy(&lock);
  //  III.  Finished:
  return(EXIT_SUCCESS);
}