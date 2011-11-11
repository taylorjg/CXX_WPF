using System;
using System.Collections;
using System.Collections.Generic;
using GalaSoft.MvvmLight;

namespace WineDemoUserControls.ViewModel
{
    /// <summary>
    /// This class contains properties that the WineList user control can data bind to.
    /// <para>
    /// Use the <strong>mvvminpc</strong> snippet to add bindable properties to this ViewModel.
    /// </para>
    /// <para>
    /// You can also use Blend to data bind with the tool's support.
    /// </para>
    /// <para>
    /// See http://www.galasoft.ch/mvvm
    /// </para>
    /// </summary>
    public class WineListViewModel : ViewModelBase
    {
        /// <summary>
        /// Initializes a new instance of the MainViewModel class.
        /// </summary>
        public WineListViewModel()
        {
            if (IsInDesignMode) {
                var products = new List<Product>();
                products.Add(Product.CreateDesignTimeInstance());
                Products = products;
            }
        }

        private IEnumerable _products = null;
        public IEnumerable Products
        {
            get
            {
                return _products;
            }
            set
            {
                if (value != _products) {
                    _products = value;
                    RaisePropertyChanged("Products");
                }
            }
        }
    }
}
