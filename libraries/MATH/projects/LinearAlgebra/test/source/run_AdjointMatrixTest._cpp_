void AdjointMatrixTest::run()
{
	bool tmp = true;
	try
	{
		testTransformation();
		if(isOk())
			std::cout<<"\tOK................testTransformation"<<std::endl;
		else
			std::cout<<"\tNOK...............testTransformation"<<std::endl;
		tmp = tmp && isOk();
		ok = true;
	}
	catch(Exceptions::Exception& ex)
	{ std::cout<<"testTransformationException occured: " << ex <<std::endl; }
	catch(...)
	{ std::cout<<"testTransformationUnknown exception"<<std::endl;  }

	try
	{
		testTransformation2();
		if(isOk())
			std::cout<<"\tOK................testTransformation2"<<std::endl;
		else
			std::cout<<"\tNOK...............testTransformation2"<<std::endl;
		tmp = tmp && isOk();
		ok = true;
	}
	catch(Exceptions::Exception& ex)
	{ std::cout<<"testTransformation2Exception occured: " << ex <<std::endl; }
	catch(...)
	{ std::cout<<"testTransformation2Unknown exception"<<std::endl;  }

	try
	{
		testTransformation3();
		if(isOk())
			std::cout<<"\tOK................testTransformation3"<<std::endl;
		else
			std::cout<<"\tNOK...............testTransformation3"<<std::endl;
		tmp = tmp && isOk();
		ok = true;
	}
	catch(Exceptions::Exception& ex)
	{ std::cout<<"testTransformation3: Exception occured: " << ex <<std::endl; }
	catch(...)
	{ std::cout<<"testTransformation3: Unknown exception"<<std::endl;  }

}
