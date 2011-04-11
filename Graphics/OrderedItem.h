#ifndef __Ascension_Collections_OrderedCollection_h__
#define __Ascension_Collections_OrderedCollection_h__

namespace Ascension
{
	namespace Graphics
	{
		namespace Collections
		{
			class OrderedItem
			{
			private:
				int _orderIndex;

			public:
				int GetOrderIndex()
				{
					return _orderIndex;
				}

				void SetOrderIndex(int value)
				{
					_orderIndex = value;
				}
			}
		}
	}
}

#endif