#ifndef __GLFramework_Updateable_h__
#define __GLFramework_Updateable_h__

#include "OrderedItem.h"

namespace GLFramework
{
	class Updateable : public OrderedItem
	{
	private:
		int _updateOrder;
		bool _isEnabled;

	public:

		Updateable();

		virtual void Update(float time)
		{
		}
		
		// Accessors
		int GetUpdateOrder()
		{
			return _updateOrder;
		}
		void SetUpdateOrder(int value);

		bool GetIsEnabled();
		void SetIsEnabled(bool value);
	};
}

#endif
